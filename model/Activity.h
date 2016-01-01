#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "NamedEntity.h"
#include <QString>

class Activity : public NamedEntity
{
public:
    Activity(pkey_t id, const QString &name);
    ~Activity();

private:

};

#endif // ACTIVITY_H
