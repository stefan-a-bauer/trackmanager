#include "Repository.h"

#include <cstddef>
#include <QtGlobal>
#include <QString>
#include <QDir>
#include <QPair>
#include <QList>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QtDebug>
#include <sqlite3.h>

#include "Exception.h"

#define COLUMNNAME_ID "id"
#define COLUMNNAME_NAME "name"
#define COLUMNNAME_DESCRIPTION "description"
#define COLUMNNAME_TOURID "tourId"
#define COLUMNNAME_GEARID "gearId"
#define COLUMNNAME_ACTIVITYID "activityId"
#define COLUMNNAME_TRACKID "trackId"
#define COLUMNNAME_GEOMETRY "geometry"
#define COLUMNNAME_TIME "time"
#define COLUMNNAME_RATING "rating"

#define SRID "4326" // WGS84

#define FOREIGN_KEY(name, foreignTable) \
    name " INTEGER REFERENCES " foreignTable "(" COLUMNNAME_ID ")"

#define FOREIGN_KEY_NOT_NULL(name, foreignTable) \
    FOREIGN_KEY(name, foreignTable) " NOT NULL"

#define TABLE_ACTIVITY "Activity"
#define TABLE_GEAR "Gear"
#define TABLE_TOUR "Tour"
#define TABLE_TRACK "Track"
#define TABLE_TRACKPOINT "TrackPoint"
#define TABLE_WAYPOINT "WayPoint"
#define TABLE_HIGHLIGHT "Highlight"

#define COLUMN_ID COLUMNNAME_ID" INTEGER PRIMARY KEY"
#define COLUMN_NAME COLUMNNAME_NAME" TEXT"
#define COLUMN_DESCRIPTION COLUMNNAME_DESCRIPTION" TEXT"
#define COLUMN_TIME COLUMNNAME_TIME" INTEGER NOT NULL"
#define COLUMN_RATING COLUMNNAME_RATING" INTEGER"

Repository::Repository()
{
}

Repository::~Repository()
{
}

void Repository::open()
{
    QString trackmanagerPath(QDir::homePath() + "/.trackmanager");
    QDir trackmanagerDir(trackmanagerPath);

    if (!trackmanagerDir.exists())
    {
        if (!trackmanagerDir.mkpath("."))
        {
            throw Exception(QString("Failed to create path '%1'.").arg(trackmanagerPath));
        }
    }

    QString dbPath(trackmanagerPath + "/data.db");

    bool dbExists = QFile(dbPath).exists();

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open())
    {
        throw Exception(QString("Failed to open database. %1").arg(m_db.lastError().text()));
    }

    execute("PRAGMA foreign_keys = ON;");

    loadSpatialite();

    if (!dbExists)
    {
        init();
    }
}

void Repository::init()
{
    execute("SELECT InitSpatialMetaData('WGS84');");

    QList< QPair<QByteArray, QByteArray> > tables;

    tables << QPair<QByteArray, QByteArray>(
        TABLE_ACTIVITY,
        COLUMN_ID ","
        COLUMN_NAME);

    tables << QPair<QByteArray, QByteArray>(
        TABLE_GEAR,
        COLUMN_ID ","
        COLUMN_NAME ","
        FOREIGN_KEY_NOT_NULL("activityId", TABLE_ACTIVITY));

    tables << QPair<QByteArray, QByteArray>(
        TABLE_TOUR,
        COLUMN_ID ","
        COLUMN_NAME ","
        COLUMN_DESCRIPTION);

    tables << QPair<QByteArray, QByteArray>(
        TABLE_TRACK,
        COLUMN_ID ","
        COLUMN_NAME ","
        COLUMN_DESCRIPTION ","
        FOREIGN_KEY_NOT_NULL(COLUMNNAME_TOURID, TABLE_TOUR) ","
        FOREIGN_KEY(COLUMNNAME_GEARID, TABLE_GEAR) ","
        FOREIGN_KEY(COLUMNNAME_ACTIVITYID, TABLE_ACTIVITY));

    tables << QPair<QByteArray, QByteArray>(
        TABLE_TRACKPOINT,
        COLUMN_ID ","
        COLUMN_TIME ","
        FOREIGN_KEY_NOT_NULL(COLUMNNAME_TRACKID, TABLE_TRACK));

    tables << QPair<QByteArray, QByteArray>(
        TABLE_WAYPOINT,
        COLUMN_ID ","
        COLUMN_NAME ","
        COLUMN_TIME ","
        FOREIGN_KEY_NOT_NULL(COLUMNNAME_TOURID, TABLE_TOUR));

    tables << QPair<QByteArray, QByteArray>(
        TABLE_HIGHLIGHT,
        COLUMN_ID ","
        COLUMN_NAME ","
        COLUMN_DESCRIPTION ","
        COLUMN_RATING ","
        FOREIGN_KEY(COLUMNNAME_ACTIVITYID, TABLE_ACTIVITY));

    QPair<QByteArray, QByteArray> table;

    foreach (table, tables)
    {
        createTable(table.first, table.second);
    }

    execute("SELECT AddGeometryColumn('" TABLE_TRACKPOINT "', '" COLUMNNAME_GEOMETRY "', " SRID ", 'POINTZ', 'XYZ');");
    execute("SELECT AddGeometryColumn('" TABLE_WAYPOINT "', '" COLUMNNAME_GEOMETRY "', " SRID ", 'POINTZ', 'XYZ');");
    execute("SELECT AddGeometryColumn('" TABLE_HIGHLIGHT "', '" COLUMNNAME_GEOMETRY "', " SRID ", 'LINESTRING', 'XY');");
}

void Repository::close()
{
    m_db.close();
}

void Repository::beginTransaction()
{
    if (!m_db.transaction())
    {
        throw Exception("Could not initiate a transaction.");
    }
}

void Repository::commitTransaction()
{
    if (!m_db.commit())
    {
        throw Exception("Could not commit the current transaction.");
    }
}

void Repository::rollbackTransaction()
{
    if (!m_db.rollback())
    {
        throw Exception("Could not rool back the current transaction.");
    }
}

pkey_t Repository::createActivity(const QString &name)
{
    QStringList keys;
    keys << COLUMNNAME_NAME;

    QList<QVariant> values;
    values << name;

    return insert(TABLE_ACTIVITY, keys, values);
}

pkey_t Repository::createGear(const QString &name, const Activity &activity)
{
    QStringList keys;
    keys << COLUMNNAME_NAME;
    keys << COLUMNNAME_ACTIVITYID;

    QList<QVariant> values;
    values << name;
    values << activity.getId();

    return insert(TABLE_GEAR, keys, values);
}

pkey_t Repository::createTour(const QString &name, const QString &description)
{
    QStringList keys;
    keys << COLUMNNAME_NAME;
    keys << COLUMNNAME_DESCRIPTION;

    QList<QVariant> values;
    values << name;
    values << description;

    return insert(TABLE_TOUR, keys, values);
}

pkey_t Repository::createTrack(const QString &name,
    const QString &description,
    pkey_t tourId,
    const Gear &gear,
    const Activity &activity)
{
    QStringList columns;
    columns << COLUMNNAME_NAME;
    columns << COLUMNNAME_DESCRIPTION;
    columns << COLUMNNAME_TOURID;
    columns << COLUMNNAME_GEARID;
    columns << COLUMNNAME_ACTIVITYID;

    QList<QVariant> values;
    values << name;
    values << description;
    values << tourId;
    values << gear.getId();
    values << activity.getId();

    return insert(TABLE_TRACK, columns, values);
}

QString doubleToString(double number)
{
    // GPSBabel uses 9, Viking uses 6
    return QString::number(number, 'f', 9);
}

QString makePointZ(double lat, double lon, double elevation)
{
    return QString("MakePointZ(%1, %2, %3, " SRID ")").arg(doubleToString(lon)).arg(doubleToString(lat)).arg(doubleToString(elevation));
}

uint getSecondsSinceEpoch(const QDateTime &time)
{
    uint secondsSinceEpoch = time.toTime_t();

    if ((int)secondsSinceEpoch < 0)
    {
        throw std::range_error(QString("The date '%s' is out of range.").arg(time.toString()).toStdString());
    }

    return secondsSinceEpoch;
}

pkey_t Repository::createTrackPoint(double lat, double lon, double elevation, const QDateTime &time, pkey_t trackId)
{
    QStringList columns;
    columns << COLUMNNAME_GEOMETRY;
    columns << COLUMNNAME_TIME;
    columns << COLUMNNAME_TRACKID;

    QStringList values;
    values << makePointZ(lat, lon, elevation);
    values << "?";
    values << "?";

    QList<QVariant> bindValues;
    bindValues << getSecondsSinceEpoch(time);
    bindValues << trackId;

    return insert(TABLE_TRACKPOINT, columns, values, bindValues);
}

pkey_t Repository::createWayPoint(const QString &name,
    double lat,
    double lon,
    double elevation,
    const QDateTime &time,
    pkey_t tourId)
{
    QStringList columns;
    columns << COLUMNNAME_NAME;
    columns << COLUMNNAME_GEOMETRY;
    columns << COLUMNNAME_TIME;
    columns << COLUMNNAME_TOURID;

    QStringList values;
    values << "?";
    values << makePointZ(lat, lon, elevation);
    values << "?";
    values << "?";

    QList<QVariant> bindValues;
    bindValues << name;
    bindValues << getSecondsSinceEpoch(time);
    bindValues << tourId;

    return insert(TABLE_WAYPOINT, columns, values, bindValues);
}

QString MakeLine(const QList<Position> &geometry)
{
    QStringList positions;

    foreach (Position position, geometry)
    {
        positions.append(QString("%1 %2)").arg(doubleToString(position.getLon())).arg(doubleToString(position.getLat())));
    }

    return QString("MakeLine(%1)").arg(positions.join(", "));
}

pkey_t Repository::createHighlight(
    const QString &name,
    const QString &description,
    const QList<Position> &geometry,
    qint32 rating,
    const Activity &activity)
{
    QStringList columns;
    columns << COLUMNNAME_NAME;
    columns << COLUMNNAME_DESCRIPTION;
    columns << COLUMNNAME_GEOMETRY;
    columns << COLUMNNAME_RATING;
    columns << COLUMNNAME_ACTIVITYID;

    QStringList unboundValues;
    unboundValues << "?";
    unboundValues << "?";
    unboundValues << MakeLine(geometry);
    unboundValues << "?";
    unboundValues << "?";

    QList<QVariant> values;
    values << name;
    values << description;
    values << rating;
    values << activity.getId();

    return insert(TABLE_HIGHLIGHT, columns, unboundValues, values);
}

QList<Activity> Repository::getActivities()
{
    QSqlQuery query(QString("SELECT * FROM " TABLE_ACTIVITY ";"));

    if (!query.exec())
    {
        throw Exception(query.lastError().text());
    }

    QList<Activity> activities;

    while (query.next())
    {
        pkey_t id = query.value(0).toLongLong();
        QString name = query.value(1).toString();
        activities.append(Activity(id, name));
    }

    return activities;
}

QList<Gear> Repository::getGear()
{
    QSqlQuery query(QString("SELECT * FROM " TABLE_GEAR ";"));

    if (!query.exec())
    {
        throw Exception(query.lastError().text());
    }

    QList<Gear> gear;

    while (query.next())
    {
        pkey_t id = query.value(0).toLongLong();
        QString name = query.value(1).toString();
        pkey_t activityId = query.value(2).toLongLong();
        gear.append(Gear(id, name, activityId));
    }

    return gear;
}

QList<Tour> Repository::getTours()
{
    QSqlQuery query(QString("SELECT * FROM " TABLE_TOUR ";"));

    if (!query.exec())
    {
        throw Exception(query.lastError().text());
    }

    QList<Tour> tours;

    while (query.next())
    {
        pkey_t id = query.value(0).toLongLong();
        auto name = query.value(1).toString();
        auto description = query.value(2).toString();
        tours.append(Tour(id, name, description));
    }

    return tours;
}

QList<Track> Repository::getTracks()
{
    QSqlQuery query(QString("SELECT * FROM " TABLE_TRACK ";"));

    if (!query.exec())
    {
        throw Exception(query.lastError().text());
    }

    QList<Track> tracks;

    while (query.next())
    {
        pkey_t id = query.value(0).toLongLong();
        QString name = query.value(1).toString();
        QString description = query.value(2).toString();
        pkey_t tourId = query.value(3).toLongLong();
        pkey_t gearId = query.value(4).toLongLong();
        pkey_t activityId = query.value(5).toLongLong();
        tracks.append(Track(id, name, description, tourId, gearId, activityId));
    }

    return tracks;
}

QList<TrackPoint> Repository::getTrackPoints(const Track &track)
{
    QStringList columns;
    columns << COLUMNNAME_ID;
    columns << COLUMNNAME_TIME;
    columns << "ST_X(p." COLUMNNAME_GEOMETRY ")";
    columns << "ST_Y(p." COLUMNNAME_GEOMETRY ")";
    columns << "ST_Z(p." COLUMNNAME_GEOMETRY ")";

    QString queryString = QString(
        "SELECT %1 FROM " TABLE_TRACKPOINT " AS p "
        "WHERE p." COLUMNNAME_TRACKID " = %2;").arg(columns.join(", ")).arg(track.getId());

    QSqlQuery query(queryString);

    if (!query.exec())
    {
        throw Exception(query.lastError().text());
    }

    QList<TrackPoint> trackPoints;

    while (query.next())
    {
        pkey_t id = query.value(0).toLongLong();
        auto time = QDateTime::fromTime_t(query.value(1).toUInt());
        auto lon = query.value(2).toDouble();
        auto lat = query.value(3).toDouble();
        auto elevation = query.value(4).toDouble();

        trackPoints.append(TrackPoint(id, lat, lon, elevation, time, track));
    }

    return trackPoints;
}

QList<WayPoint> Repository::getWayPoints(const Tour &tour)
{
    QStringList columns;
    columns << COLUMNNAME_ID;
    columns << COLUMNNAME_NAME;
    columns << COLUMNNAME_TIME;
    columns << "ST_X(p." COLUMNNAME_GEOMETRY ")";
    columns << "ST_Y(p." COLUMNNAME_GEOMETRY ")";
    columns << "ST_Z(p." COLUMNNAME_GEOMETRY ")";

    QString queryString = QString(
        "SELECT %1 FROM " TABLE_WAYPOINT " AS p "
        "WHERE p." COLUMNNAME_TOURID " = %2;").arg(columns.join(", ")).arg(tour.getId());

    QSqlQuery query(queryString);

    if (!query.exec())
    {
        throw Exception(query.lastError().text());
    }

    QList<WayPoint> wayPoints;

    while (query.next())
    {
        pkey_t id = query.value(0).toLongLong();
        auto name = query.value(1).toString();
        auto time = QDateTime::fromTime_t(query.value(2).toUInt());
        auto lon = query.value(3).toDouble();
        auto lat = query.value(4).toDouble();
        auto elevation = query.value(5).toDouble();

        wayPoints.append(WayPoint(id, name, lat, lon, elevation, time, tour));
    }

    return wayPoints;
}

pkey_t Repository::insert(const QString &table, const QStringList &columns, const QList<QVariant> &bindValues)
{
    if (columns.length() != bindValues.length())
    {
        throw std::invalid_argument(
            QString("Could not insert row into toable '%1'. The number of columns (%2) does not match the number of values (%3).")
                .arg(table)
                .arg(columns.length())
                .arg(bindValues.length())
                .toStdString());
    }

    QStringList values;

    for (int i = 0; i < columns.length(); i++)
    {
        values.append("?");
    }

    return insert(table, columns, values, bindValues);
}


pkey_t Repository::insert(const QString &table, const QStringList &columns, const QStringList &values, const QList<QVariant> &bindValues)
{
    if (columns.length() != values.length())
    {
        throw std::invalid_argument(
            QString("Could not insert row into toable '%1'. The number of columns (%2) does not match the number of values (%3).")
                .arg(table)
                .arg(columns.length())
                .arg(bindValues.length())
                .toStdString());
    }

    QString sql = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(table).arg(columns.join(", ")).arg(values.join(", "));

    QSqlQuery query;

    if (!query.prepare(sql))
    {
        throw Exception(query.lastError().text());
    }

    foreach (const QVariant &value, bindValues)
    {
        query.addBindValue(value);
    }

    if (!query.exec())
    {
        throw Exception(query.lastError().text());
    }

    if (!query.exec("SELECT last_insert_rowid();"))
    {
        throw Exception(query.lastError().text());
    }

    if (!query.next())
    {
        throw Exception(std::string("Could not get the id of the last inserted row."));
    }

    return query.value(0).toLongLong();
}

void Repository::createTable(const char *name, const char *columns)
{
    return execute(
        QString("CREATE TABLE %1 (%2);").arg(name).arg(columns));
}

void Repository::execute(const QString &sql)
{
    QSqlQuery query;

    if (!query.exec(sql))
    {
        throw Exception(
            QString("Failed to execute SQL '%1'. Error: %2\n").arg(sql).arg(query.lastError().text()).toStdString());
    }
}

void Repository::loadSpatialite()
{
    QVariant v = m_db.driver()->handle();

    if (!v.isValid())
    {
        throw Exception("Unable to get database driver handle.");
    }

    if (strcmp(v.typeName(), "sqlite3*") != 0)
    {
        // No SQLite DB. Could be some other GIS DB (PostGIS?).
        return;
    }

    sqlite3 *handle = *static_cast<sqlite3 **>(v.data());

    if (handle == NULL)
    {
        throw Exception("SQLite handle is NULL.");
    }

    if (sqlite3_enable_load_extension(handle, 1) != SQLITE_OK)
    {
        throw Exception("Failed to enable SQLite extension loading.");
    }

    char *error = NULL;

    if (sqlite3_load_extension(handle, "mod_spatialite", NULL, &error) != SQLITE_OK)
    {
        auto msg = QString("Failed to load SpatiaLite. %1").arg(error);
        sqlite3_free(error);
        throw Exception(msg);
    }

    if (sqlite3_enable_load_extension(handle, 0) != SQLITE_OK)
    {
        throw Exception("Failed to disable SQLite extension loading.");
    }
}
