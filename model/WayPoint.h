#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "Point.h"
#include "Tour.h"

class WayPoint : public NamedEntity, public Point
{
public:
    WayPoint(
        pkey_t id,
        const QString &name,
        double lat,
        double lon,
        double elevation,
        const QDateTime &time,
        pkey_t tourId);

    ~WayPoint();

    pkey_t getTourId() const
    {
        return m_tourId;
    }

private:
    pkey_t m_tourId;
};

#endif
