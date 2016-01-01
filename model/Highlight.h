#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <QList>
#include "DescribedEntity.h"
#include "Activity.h"
#include "Position.h"

class Highlight : public DescribedEntity
{
public:
    Highlight(
        pkey_t id,
        const QString &name,
        const QString &description,
        const QList<Position> &geometry,
        qint32 rating,
        const Activity &activity);

    ~Highlight();

    const QList<Position> &getGeometry() const
    {
        return m_geometry;
    }

    qint32 getRating() const
    {
        return m_rating;
    }

    pkey_t getActivityId() const
    {
        return m_activityId;
    }

private:
    QList<Position> m_geometry;
    qint32 m_rating;
    pkey_t m_activityId;
};

#endif
