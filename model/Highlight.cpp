#include "Highlight.h"

Highlight::Highlight(
    pkey_t id,
    const QString &name,
    const QString &description,
    const QList<Position> &geometry,
    qint32 rating,
    const Activity &activity) :
    DescribedEntity(id, name, description),
    m_geometry(geometry),
    m_rating(rating),
    m_activityId(activity.getId())
{
}
