#include "Layer.h"

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

bool Layer::render(
    Marble::GeoPainter *painter,
    Marble::ViewportParams *viewport,
    const QString &renderPos,
    Marble::GeoSceneLayer *layer)
{
    painter->setPen(QPen(QBrush(Qt::red), 3.0, Qt::SolidLine, Qt::RoundCap));

    auto tracks = m_pRepository->getTracks();

    foreach (auto track, tracks)
    {
         auto trackPoints = m_pRepository->getTrackPoints(track);

         Marble::GeoDataLineString lineString;

         foreach (auto trackPoint, trackPoints)
         {
            lineString.append(Marble::GeoDataCoordinates(
                trackPoint.getLon(),
                trackPoint.getLat(),
                trackPoint.getElevation(),
                Marble::GeoDataCoordinates::Degree));
         }

         painter->drawPolyline(
             lineString,
             track.getName());
    }

    return true;
}
