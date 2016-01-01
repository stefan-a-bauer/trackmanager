#ifndef TOUR_H
#define TOUR_H

#include "DescribedEntity.h"

class Tour : public DescribedEntity
{
public:
    Tour(pkey_t id, const QString &name, const QString &description);
    ~Tour();

private:
};

#endif
