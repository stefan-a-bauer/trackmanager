#ifndef ABSTRACTIMPORTER_H
#define ABSTRACTIMPORTER_H

#include <QString>

#include "abstractmodel.h"

class AbstractImporter
{
public:
    AbstractImporter();
    virtual ~AbstractImporter();

    virtual void Import(AbstractModel *model, const QString &fileName) = 0;
};

#endif // ABSTRACTIMPORTER_H
