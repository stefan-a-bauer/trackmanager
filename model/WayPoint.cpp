#include "WayPoint.h"

WayPoint::WayPoint(pkey_t id,
    const QString &name,
    double lat,
    double lon,
    double elevation,
    const QDateTime &time,
    const Tour &tour) :
    NamedEntity(id, name),
    Point(lat, lon, elevation, time),
    m_tourId(tour.getId())
{
}

WayPoint::~WayPoint()
{
}
