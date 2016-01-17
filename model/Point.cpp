#include "Point.h"
#include "Exception.h"

Point::Point(double lat, double lon, double elevation, const QDateTime &time) :
    Position(lat, lon),
    m_elevation(elevation),
    m_time(time)
{
    if (elevation < -1000 || elevation > 18000)
    {
        throw Exception(QString("Invalid elevation: %1 m").arg(elevation));
    }

    if (!time.isValid())
    {
        throw Exception("Invalid timestamp.");
    }
}

Point::~Point()
{
}
