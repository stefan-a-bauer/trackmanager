#ifndef DESCRIBEDENTITY_H
#define DESCRIBEDENTITY_H

#include "NamedEntity.h"

class DescribedEntity : public NamedEntity
{
public:
    DescribedEntity(pkey_t id, const QString &name, const QString &description);
    ~DescribedEntity();

    const QString &getDescription() const
    {
        return m_description;
    }

private:
    QString m_description;
};

#endif // ENTITY_H
