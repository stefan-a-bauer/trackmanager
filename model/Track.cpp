#include "Track.h"

Track::Track(pkey_t id,
    const QString &name,
    const QString &description,
    pkey_t tourId,
    pkey_t gearId,
    pkey_t activityId) :
    DescribedEntity(id, name, description),
    m_tourId(tourId),
    m_gearId(gearId),
    m_activityId(activityId)
{
}

Track::~Track()
{
}
