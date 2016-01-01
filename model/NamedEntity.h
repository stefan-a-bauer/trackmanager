#ifndef NAMEDENTITY_H
#define NAMEDENTITY_H

#include "Entity.h"
#include <QString>

class NamedEntity : public Entity
{
public:
    NamedEntity(pkey_t id, const QString &name);
    ~NamedEntity();

    const QString & getName() const
    {
        return m_name;
    }

private:
    QString m_name;
};

#endif
