#include "Position.h"
#include "Exception.h"

Position::Position(double lat, double lon) :
    m_lat(lat),
    m_lon(lon)
{
    if (lat > 90 || lat < -90 || lon > 180 || lon < -180)
    {
        throw Exception(QString("Invalid position: Latitide %1°, longitude %2°.").arg(lat).arg(lon));
    }
}

Position::~Position()
{
}
