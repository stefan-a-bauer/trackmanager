#include "NamedEntity.h"

NamedEntity::NamedEntity(pkey_t id, const QString &name) :
    Entity(id),
    m_name(name)
{
}

NamedEntity::~NamedEntity()
{
}
