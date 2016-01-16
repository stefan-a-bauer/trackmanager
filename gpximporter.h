#ifndef GPXIMPORTER_H
#define GPXIMPORTER_H

#include "abstractimporter.h"

#include <QDomElement>

class GpxImporter : public AbstractImporter
{
public:
    GpxImporter();
    ~GpxImporter();

    virtual pkey_t import(Repository &repository, const QString &fileName, const Gear &gear, const Activity &activity);

private:
    void parseTrack(Repository &repository, const QDomElement &element, pkey_t tourId, const Gear &gear, const Activity &activity);
    void parseTrackPoint(Repository &repository, const QDomElement &element, pkey_t trackId);
    void parseWayPoint(Repository &repository, const QDomElement &element, pkey_t tourId);

    QDateTime m_lastTime;
};

#endif // GPXIMPORTER_H
