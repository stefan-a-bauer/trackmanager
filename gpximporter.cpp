#include "gpximporter.h"

#include <QDebug>
#include <QDomDocument>
#include <QFile>

#include "Exception.h"

#define ELEMENT_WPT "wpt"
#define ELEMENT_TRK "trk"
#define ELEMENT_TRKSEG "trkseg"
#define ELEMENT_TRKPT "trkpt"

GpxImporter::GpxImporter()
{
}

GpxImporter::~GpxImporter()
{
}

QString parseName(const QDomElement &element)
{
    QDomElement name = element.firstChildElement("name");
    return name.text();
}

QString getPositionString(const QDomElement &element)
{
    return QString("at line %1, column %2").arg(element.lineNumber()).arg(element.columnNumber());
}

double parseDoubleAttribute(const QDomElement &element, const QString &attributeName)
{
    bool ok;
    auto value = element.attribute(attributeName).toDouble(&ok);

    if (!ok)
    {
        throw Exception(
            QString(
                "The value of the '%1' attribute of the element '%2' %3 is not a floating point number.")
                .arg(attributeName)
                .arg(element.tagName())
                .arg(getPositionString(element)));
    }

    return value;
}

double parseLat(const QDomElement &element)
{
    return parseDoubleAttribute(element, "lat");
}

double parseLon(const QDomElement &element)
{
    return parseDoubleAttribute(element, "lon");
}

double parseElevation(const QDomElement &element)
{
    QDomElement ele = element.firstChildElement("ele");

    bool ok;
    double elevation = ele.text().toDouble(&ok);

    if (!ok)
    {
        elevation = NAN;
    }

    return elevation;
}

QDateTime parseTime(const QDomElement &element)
{
    QDomElement timeElement = element.firstChildElement("time");

    if (timeElement.isNull())
    {
        throw Exception(
            QString("Missing timestamp %1.").arg(getPositionString(element)));
    }

    auto time = QDateTime::fromString(timeElement.text(), Qt::ISODate);

    if (!time.isValid())
    {
        throw Exception(
            QString("Invalid timestamp %1.").arg(getPositionString(timeElement)));
    }

    return time;
}

void parseWayPoint(Repository &repository, const QDomElement &element, pkey_t tourId)
{
    auto name = parseName(element);
    auto lat = parseLat(element);
    auto lon = parseLon(element);
    auto elevation = parseElevation(element);
    auto time = parseTime(element);

    repository.createWayPoint(name, lat, lon, elevation, time, tourId);
}

void ParseTrackPoint(Repository &repository, const QDomElement &element, pkey_t trackId)
{
    auto lat = parseLat(element);
    auto lon = parseLon(element);
    auto elevation = parseElevation(element);
    auto time = parseTime(element);

    repository.createTrackPoint(lat, lon, elevation, time, trackId);
}

void ParseTrack(Repository &repository, const QDomElement &element, pkey_t tourId, const Gear &gear, const Activity &activity)
{
    QDomElement nameElement = element.firstChildElement("name");
    QDomElement descriptionElement = element.firstChildElement("desc");

    QString name = nameElement.isText() ? nameElement.text() : QString();
    QString description = descriptionElement.isText() ? descriptionElement.text() : QString();

    auto trackId = repository.createTrack(name, description, tourId, gear, activity);

    for (QDomElement seg = element.firstChildElement(ELEMENT_TRKSEG); !seg.isNull(); seg = seg.nextSiblingElement(ELEMENT_TRKSEG))
    {
        for (QDomElement point = seg.firstChildElement(ELEMENT_TRKPT); !point.isNull(); point = point.nextSiblingElement(ELEMENT_TRKPT))
        {
            ParseTrackPoint(repository, point, trackId);
        }
    }
}

pkey_t GpxImporter::Import(Repository &repository, const QString &fileName, const Gear &gear, const Activity &activity)
{
    QDomDocument document;
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
    {
        throw Exception(QString("Could not open file '%1'.").arg(fileName));
    }

    if (!document.setContent(&file))
    {
        file.close();
        throw Exception(QString("Could load XML from file '%1'.").arg(fileName));
    }

    file.close();


    QDomElement documentElement = document.documentElement();

    repository.beginTransaction();

    try
    {
        auto tourId = repository.createTour("name", "description");

        for (QDomElement wpt = documentElement.firstChildElement(ELEMENT_WPT); !wpt.isNull(); wpt = wpt.nextSiblingElement(ELEMENT_WPT))
        {
            parseWayPoint(repository, wpt, tourId);
        }

        for (QDomElement trk = documentElement.firstChildElement(ELEMENT_TRK); !trk.isNull(); trk = trk.nextSiblingElement(ELEMENT_TRK))
        {
            ParseTrack(repository, trk, tourId, gear, activity);
        }

        repository.commitTransaction();

        return tourId;
    }
    catch (const Exception &exception)
    {
        repository.rollbackTransaction();

        throw;
    }
}


