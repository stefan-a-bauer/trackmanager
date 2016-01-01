#ifndef ENTITY_H
#define ENTITY_H

#include "../types.h"

class Entity
{
public:
    Entity(pkey_t id);
    ~Entity();

    pkey_t getId() const
    {
        return m_id;
    }

private:
    pkey_t m_id;
};

#endif // ENTITY_H
