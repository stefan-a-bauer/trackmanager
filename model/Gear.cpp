#include "Gear.h"

Gear::Gear(pkey_t id, const QString &name, pkey_t activityId) :
    NamedEntity(id, name),
    m_activityId(activityId)
{
}

Gear::~Gear()
{
}
