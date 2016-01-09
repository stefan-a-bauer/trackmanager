#include "Layer.h"

#include "Exception.h"
#include "tools.h"

#include <marble/GeoDataCoordinates.h>
#include <marble/GeoPainter.h>
#include <marble/ViewportParams.h>

Layer::Layer(QObject *parent, Repository *pRepository) :
    QObject(parent),
    m_pRepository(pRepository)
{
    m_pCache = new Cache(this, pRepository);
    m_renderPosition << "SURFACE";
}

QStringList Layer::renderPosition() const
{
    return m_renderPosition;
}

bool Layer::render(
    Marble::GeoPainter *painter,
    Marble::ViewportParams *viewport,
    const QString &renderPos,
    Marble::GeoSceneLayer *layer)
{
    const qreal width = 3.0;
    const int minZoomForWayPoints = 2200;

    try
    {
        painter->setPen(QPen(QBrush(Qt::red), width, Qt::SolidLine, Qt::RoundCap));

        qreal north, south, east, west;

        viewport->viewLatLonAltBox().boundaries(north, south, east, west, Marble::GeoDataCoordinates::Degree);

        Box box(Position(south, west), Position(north, east));

        auto tracks = m_pRepository->getTracks(box);

        foreach (auto track, tracks)
        {
            Marble::GeoDataLineString lineString = m_pCache->getTrackLineString(track);

            painter->drawPolyline(lineString);
        }

        if (m_zoom > minZoomForWayPoints)
        {
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
        }

        return true;
    }
    catch (Exception &exception)
    {
        qDebug() << exception.what();
        return false;
    }
}

void Layer::onZoomChanged(int newZoom)
{
    m_zoom = newZoom;
}

void Layer::onVisibleLatLonAltBoxChanged(const Marble::GeoDataLatLonAltBox &box)
{
    m_box = box;
}
