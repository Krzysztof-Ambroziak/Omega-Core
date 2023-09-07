/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "TileRenderer.hpp"
#include "../models/api/IMapModel.hpp"

#include <QPainter>
#include <QVector>

TileRenderer::TileRenderer(const IMapModel* mapModel,
                           const IScreenModel* screenModel) :
        m_mapModel(mapModel),
        m_screenModel(screenModel) {}

void TileRenderer::setTilePositions(const QVector<oc::TilePosition>& positions) {
    m_positions = positions;
}

void TileRenderer::render(QPainter& painter) {
    foreach (const auto& position, m_positions) {
        painter.drawPixmap(position.offset.xOffset,
                           position.offset.yOffset,
                           m_mapModel->tile(position.position));
    }
}
