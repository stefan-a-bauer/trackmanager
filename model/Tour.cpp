#include "Tour.h"

Tour::Tour(pkey_t id, const QString &name, const QString &description) :
    DescribedEntity(id, name, description)
{
}

Tour::~Tour()
{
}
