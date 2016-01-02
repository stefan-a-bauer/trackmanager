#include "Cache.h"

#include "tools.h"

Cache::Cache(QObject *parent, Repository *pRepository) :
    QObject(parent),
    m_pRepository(pRepository)
{
}

Marble::GeoDataLineString Cache::getTrackLineString(const Track &track)
{
    const auto trackId = track.getId();

    if (m_cache.contains(trackId))
    {
        return m_cache.value(trackId);
    }
    else
    {
        Marble::GeoDataLineString lineString;

        auto trackPoints = m_pRepository->getTrackPoints(track);

        foreach (auto trackPoint, trackPoints)
        {
            lineString.append(PointToCoordinates(trackPoint));
        }

        m_cache.insert(trackId, lineString);

        return lineString;
    }
}

void Cache::invalidateTrack(pkey_t trackId)
{
    m_cache.remove(trackId);
}
