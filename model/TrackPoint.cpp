#include "TrackPoint.h"

TrackPoint::TrackPoint(pkey_t id, double lat, double lon, double elevation, const QDateTime &time, const Track &track) :
    Entity(id),
    Point(lat, lon, elevation, time),
    m_trackId(track.getId())
{
}
