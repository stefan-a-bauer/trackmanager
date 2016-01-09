#ifndef LAYER_H
#define LAYER_H

#include <marble/LayerInterface.h>
#include <marble/GeoDataLineString.h>
#include "Repository.h"
#include "Cache.h"

class Layer : public QObject, public Marble::LayerInterface
{
    Q_OBJECT

public:
    Layer(QObject *parent, Repository *pRepository);
    QStringList renderPosition() const;
    bool render(
        Marble::GeoPainter *painter,
        Marble::ViewportParams *viewport,
        const QString &renderPos,
        Marble::GeoSceneLayer *layer);

public slots:
    void onZoomChanged(int newZoom);

private:
    QStringList m_renderPosition;
    Repository *m_pRepository;
    Cache *m_pCache;
    QHash<pkey_t, Marble::GeoDataLineString> m_cache;
    int m_zoom;
};

#endif
