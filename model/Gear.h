#ifndef GEAR_H
#define GEAR_H

#include "NamedEntity.h"

class Gear : public NamedEntity
{
public:
    Gear(pkey_t id, const QString &name, pkey_t activityId);
    ~Gear();

    pkey_t getActivityId() const
    {
        return m_activityId;
    }

private:
    pkey_t m_activityId;
};

#endif // GEAR_H
