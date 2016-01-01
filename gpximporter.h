#ifndef GPXIMPORTER_H
#define GPXIMPORTER_H

#include "abstractimporter.h"

#include <QDomElement>

class GpxImporter : public AbstractImporter
{
public:
    GpxImporter();
    ~GpxImporter();

    virtual pkey_t Import(Repository &repository, const QString &fileName, const Gear &gear, const Activity &activity);
};

#endif // GPXIMPORTER_H
