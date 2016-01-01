#include "Point.h"

Point::Point(double lat, double lon, double elevation, const QDateTime &time) :
    Position(lat, lon),
    m_elevation(elevation),
    m_time(time)
{
}

Point::~Point()
{
}
