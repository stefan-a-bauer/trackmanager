#ifndef TRACK_H
#define TRACK_H

#include "Tour.h"
#include "Gear.h"
#include "Activity.h"

class Track : public DescribedEntity
{
public:
    Track(
        pkey_t id,
        const QString &name,
        const QString &description,
        const Tour &tour,
        const Gear &gear,
        const Activity &activity);

    ~Track();

    pkey_t getTourId() const
    {
        return m_tourId;
    }

    pkey_t getGearId() const
    {
        return m_gearId;
    }

    pkey_t getActivityId() const
    {
        return m_activityId;
    }

private:
    pkey_t m_tourId;
    pkey_t m_gearId;
    pkey_t m_activityId;
};

#endif
