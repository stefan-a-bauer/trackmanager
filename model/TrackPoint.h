#ifndef TRACKPOINT_H
#define TRACKPOINT_H

#include "Point.h"
#include "Track.h"

class TrackPoint : public Entity, public Point
{
public:
    TrackPoint(pkey_t id, double lat, double lon, double elevation, const QDateTime &time, const Track &track);
    ~TrackPoint();

    pkey_t getTrackId() const
    {
        return m_trackId;
    }

private:
    pkey_t m_trackId;
};

#endif
