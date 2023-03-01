/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef ISOMETRICTILERENDERER_HPP
#define ISOMETRICTILERENDERER_HPP

#include "api/IRenderer.hpp"
#include "Commons.hpp"

#include <QSize>
#include <QVector>

class IMapModel;

namespace ld {
struct MapSize;
}

class IsometricTileRenderer : public IRenderer {
private:
    struct ExtPosition {
        ld::Position mapPosition;
        oc::Offset tilePosition;
    };

// IRenderer interface
public:
    void render(QPainter& painter) override;
    
    oc::RendererType type() const override;

public:
    IsometricTileRenderer();
    
    void setMapModel(const IMapModel* mapModel);
    
    void setTilePositions(oc::Rotation rotation = oc::ROTATION_0_DEG);
    
    void setTileSize(const QSize& size);

private:
    const IMapModel* m_mapModel;
    
    oc::Rotation m_rotation;
    
    QSize m_tileSize;
    
    QVector<ExtPosition> m_positions;
};

#endif  // ISOMETRICTILERENDERER_HPP
