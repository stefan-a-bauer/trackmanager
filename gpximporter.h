#ifndef GPXIMPORTER_H
#define GPXIMPORTER_H

#include "abstractimporter.h"

class GpxImporter : public AbstractImporter
{
public:
    GpxImporter();
    ~GpxImporter();

    virtual void Import(AbstractModel *model, const QString &fileName);
};

#endif // GPXIMPORTER_H
