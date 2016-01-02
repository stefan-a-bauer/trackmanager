#include "tools.h"

Marble::GeoDataCoordinates PointToCoordinates(const Point &point)
{
    return Marble::GeoDataCoordinates(
        point.getLon(),
        point.getLat(),
        point.getElevation(),
        Marble::GeoDataCoordinates::Degree);
}
