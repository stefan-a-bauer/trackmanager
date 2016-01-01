#include "DescribedEntity.h"

DescribedEntity::DescribedEntity(pkey_t id, const QString &name, const QString &description) :
    NamedEntity(id, name),
    m_description(description)
{
}

DescribedEntity::~DescribedEntity()
{
}
