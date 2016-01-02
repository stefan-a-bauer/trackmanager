#ifndef TOOLS_H
#define TOOLS_H

#include "Point.h"

#include <marble/GeoDataLineString.h>

Marble::GeoDataCoordinates PointToCoordinates(const Point &point);

#endif
