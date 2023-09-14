/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "TileRenderer.hpp"
#include "../models/api/IMapModel.hpp"
#include "../models/api/IScreenModel.hpp"

#include <QPainter>

TileRenderer::TileRenderer(const IMapModel* const mapModel,
                           const IScreenModel* const screenModel) :
        m_mapModel(mapModel),
        m_screenModel(screenModel) {}

void TileRenderer::setTilePositions(const QVector<oc::TilePosition>& positions) {
    m_positions = positions;
}

void TileRenderer::render(QPainter& painter) {
    const auto& tileHalfSize = m_mapModel->tileHalfSize();
    const auto& originPoint = m_mapModel->originPoint();
    const auto& screenSize = m_screenModel->centerPoint();
    const auto xTranslate = originPoint.x() + screenSize.x() - tileHalfSize.width();
    const auto yTranslate = originPoint.y() + screenSize.y() - tileHalfSize.height();
    
    foreach (const auto& position, m_positions) {
        painter.drawPixmap(position.offset.xOffset + xTranslate,
                           position.offset.yOffset + yTranslate,
                           m_mapModel->tile(position.position));
    }
}
