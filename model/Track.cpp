#include "Track.h"

Track::Track(
    pkey_t id,
    const QString &name,
    const QString &description,
    const Tour &tour,
    const Gear &gear,
    const Activity &activity) :
    DescribedEntity(id, name, description),
    m_tourId(tour.getId()),
    m_gearId(gear.getId()),
    m_activityId(activity.getId())
{
}

Track::~Track()
{
}
