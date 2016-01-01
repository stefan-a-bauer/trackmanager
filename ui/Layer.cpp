#include "Layer.h"

#include "Exception.h"

#include <marble/GeoDataLineString.h>
#include <marble/GeoDataCoordinates.h>
#include <marble/GeoPainter.h>

Layer::Layer(QObject *parent, Repository *pRepository) :
    QObject(parent),
    m_pRepository(pRepository)
{
    m_renderPosition << "SURFACE";
}

QStringList Layer::renderPosition() const
{
    return m_renderPosition;
}

Marble::GeoDataCoordinates PointToCoordinates(const Point &point)
{
    return Marble::GeoDataCoordinates(
        point.getLon(),
        point.getLat(),
        point.getElevation(),
        Marble::GeoDataCoordinates::Degree);
}

bool Layer::render(
    Marble::GeoPainter *painter,
    Marble::ViewportParams *viewport,
    const QString &renderPos,
    Marble::GeoSceneLayer *layer)
{
    const qreal width = 3.0;

    try
    {
        painter->setPen(QPen(QBrush(Qt::red), width, Qt::SolidLine, Qt::RoundCap));

        auto tracks = m_pRepository->getTracks();

        foreach (auto track, tracks)
        {
             auto trackPoints = m_pRepository->getTrackPoints(track);

             Marble::GeoDataLineString lineString;

             foreach (auto trackPoint, trackPoints)
             {
                lineString.append(PointToCoordinates(trackPoint));
             }

             painter->drawPolyline(lineString, track.getName());
        }

        painter->setPen(QPen(QBrush(Qt::black), width));

        auto tours = m_pRepository->getTours();

        foreach (auto tour, tours)
        {
            auto wayPoints = m_pRepository->getWayPoints(tour);

            foreach (auto wayPoint, wayPoints)
            {
                auto coordinates = PointToCoordinates(wayPoint);

                painter->drawPoint(coordinates);
                painter->drawText(coordinates, wayPoint.getName());
            }
        }

        return true;
    }
    catch (Exception &exception)
    {
        qDebug() << exception.what();
        return false;
    }
}
