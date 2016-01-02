#ifndef CACHE_H
#define CACHE_H

#include <marble/GeoDataLineString.h>
#include "Repository.h"

class Cache : public QObject
{
    Q_OBJECT

public:
    Cache(QObject *parent, Repository *pRepository);

    Marble::GeoDataLineString getTrackLineString(const Track &track);

public slots:
    void invalidateTrack(pkey_t trackId);

private:
    Repository *m_pRepository;
    QHash<pkey_t, Marble::GeoDataLineString> m_cache;
};

#endif
