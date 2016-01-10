#include "WayPoint.h"

WayPoint::WayPoint(pkey_t id,
    const QString &name,
    double lat,
    double lon,
    double elevation,
    const QDateTime &time,
    pkey_t tourId) :
    NamedEntity(id, name),
    Point(lat, lon, elevation, time),
    m_tourId(tourId)
{
}

WayPoint::~WayPoint()
{
}
