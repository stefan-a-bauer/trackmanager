#ifndef LAYER_H
#define LAYER_H

#include <marble/LayerInterface.h>
#include "Repository.h"

class Layer : public QObject, public Marble::LayerInterface
{
public:
    Layer(QObject *parent, Repository *repository);
    QStringList renderPosition() const;
    bool render(
        Marble::GeoPainter *painter,
        Marble::ViewportParams *viewport,
        const QString &renderPos,
        Marble::GeoSceneLayer *layer);

private:
    QStringList m_renderPosition;
    Repository *m_pRepository;
};

#endif
