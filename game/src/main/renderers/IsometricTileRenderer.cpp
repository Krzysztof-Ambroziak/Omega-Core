/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "IsometricTileRenderer.hpp"
#include "../models/api/IMapModel.hpp"
#include "Commons.hpp"

#include <QPainter>

void IsometricTileRenderer::render(QPainter& painter) {
    int i = 0;
    for(const ExtPosition& position : m_positions) {
        const QPixmap* image = m_mapModel->tile(position.mapPosition);
        painter.drawPixmap(position.tilePosition.xOffset,
                           position.tilePosition.yOffset,
                           *image);
    }
}

oc::RendererType IsometricTileRenderer::type() const {
    return oc::TILE_RENDERER;
}

IsometricTileRenderer::IsometricTileRenderer() :
        m_mapModel(nullptr),
        m_rotation(oc::UNDEFINED_ROTATION) {}

void IsometricTileRenderer::setMapModel(const IMapModel* mapModel) {
    m_mapModel = mapModel;
}

void IsometricTileRenderer::setTilePositions(oc::Rotation rotation) {
    const int r = m_mapModel->mapSize().rows;
    const int c = m_mapModel->mapSize().columns;
    const int tileWidth = m_tileSize.width();
    const int tileHeight = m_tileSize.height();
    const int size = r * c;
    
    if(size == m_positions.size() && m_rotation == rotation)
        return;
    
    if(size != m_positions.size())
        m_positions.resize(size);
    
    const int cI = c - 1;
    const int rI = r - 1;
    const int sumI = r + c - 1;
    const int halfWidth = tileWidth / 2;
    const int halfHeight = tileHeight / 2;
    int index = 0;
    for(int i = 0, x = 0; i < sumI; i++, x = 0)
        for(int j = 0; j <= i; j++) {
            int row = -1;
            int col = -1;
            
            switch(rotation) {
            case oc::ROTATION_0_DEG:
                row = j;
                col = cI - i + j;
                break;
            case oc::ROTATION_90_DEG:
                row = rI - i + j;
                col = cI - j;
                break;
            case oc::ROTATION_180_DEG:
                col = i - j;
                row = rI - j;
                break;
            case oc::ROTATION_270_DEG:
                row = i - j;
                col = j;
                break;
            default: {}  // no action
            }
            
            if(row < 0 || row >= r || col < 0 || col >= c)
                continue;
            
            const ld::Position mapPos{col, row};
            const int xx = (i < r) ? -i * halfWidth - halfWidth + (x * tileWidth)
                                   : -(2 * r - 2 - i) * halfWidth - halfWidth + (x * tileWidth);
            const oc::Offset offset{xx, i * halfHeight};
            m_positions[index++] = {mapPos, offset};
            x++;
        }
}

void IsometricTileRenderer::setTileSize(const QSize& size) {
    m_tileSize = size;
}
