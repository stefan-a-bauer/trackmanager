#ifndef POINT_H
#define POINT_H

#include <QDateTime>
#include "Position.h"

class Point : public Position
{
public:
    Point(double lat, double lon, double elevation, const QDateTime &time);
    ~Point();

    double getElevation() const
    {
        return m_elevation;
    }

    const QDateTime &getTime() const
    {
        return m_time;
    }

private:
    double m_elevation;
    QDateTime m_time;
};

#endif
