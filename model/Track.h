#ifndef TRACK_H
#define TRACK_H

#include "Tour.h"
#include "Gear.h"
#include "Activity.h"
#include "Box.h"

class Track : public DescribedEntity
{
public:
    Track(
        pkey_t id,
        const QString &name,
        const QString &description,
        pkey_t tourId,
        pkey_t gearId,
        pkey_t activityId,
        const Box &box);

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

    const Box &getBox() const
    {
        return m_box;
    }

private:
    pkey_t m_tourId;
    pkey_t m_gearId;
    pkey_t m_activityId;
    Box m_box;
};

#endif
