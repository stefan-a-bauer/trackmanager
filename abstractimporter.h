#ifndef ABSTRACTIMPORTER_H
#define ABSTRACTIMPORTER_H

#include <QString>

#include "Repository.h"

class AbstractImporter
{
public:
    AbstractImporter();
    virtual ~AbstractImporter();

    virtual pkey_t Import(Repository &repository, const QString &fileName, const Gear &gear, const Activity &activity) = 0;
};

#endif // ABSTRACTIMPORTER_H
