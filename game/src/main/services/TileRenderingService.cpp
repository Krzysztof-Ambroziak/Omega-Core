/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "TileRenderingService.hpp"
#include "../renderers/TileRenderer.hpp"

#include <QSize>

TileRenderingService::TileRenderingService(TileRenderer* const m_tileRenderer) :
        m_tileRenderer(m_tileRenderer) {}

void TileRenderingService::changeTileQueue(const ld::MapSize& mSize, const QSize& tSize) {
    static QSize tileSize;
    static QSize halfTileSize;
    
    if(tileSize == tSize && m_mapSize.rows == mSize.rows && m_mapSize.columns == mSize.columns)
        return;
    if(tileSize != tSize) {
        tileSize = tSize;
        halfTileSize = tileSize / 2;
    }
    if(m_mapSize.rows != mSize.rows || m_mapSize.columns != mSize.columns) {
        m_mapSize = mSize;
        m_positions.resize(m_mapSize.rows * m_mapSize.columns);
    }
    
    // NOTE jeśli będą inne mapy (ortogonalne), to wyodrębnić poniższy fragment do Strategy Pattern
    int index = 0;
    int indexEnd = m_mapSize.rows * m_mapSize.columns - 1;
    const int row1 = m_mapSize.rows - 1;
    const int col1 = m_mapSize.columns - 1;
    for(int i = 0; i < m_mapSize.rows; i++)
        for(int j = 0; j <= i; j++) {
            const int xOffset = (j * tileSize.width()) - (i * halfTileSize.width());
            
            m_positions[index].position = {i - j, j};
            m_positions[indexEnd].position = {row1 - j, col1 - i + j};
            m_positions[index++].offset = {xOffset, (i - row1) * halfTileSize.height()};
            m_positions[indexEnd--].offset = {xOffset, (row1 - i) * halfTileSize.height()};
        }
    
    m_tileRenderer->setTilePositions(m_positions);
}

void TileRenderingService::rotate(oc::DirectionOfRotation dor) {
    if(m_positions.isEmpty())
        return;
    
    const auto side = m_mapSize.rows - 1;
    if(dor == oc::DOR_CLOCKWISE)
        for(auto it = m_positions.begin(); it < m_positions.end(); it++) {
            auto& pos = it->position;
            const auto row = pos.row;
            pos.row = side - pos.column;
            pos.column = row;
        }
    else
        for(auto it = m_positions.begin(); it < m_positions.end(); it++) {
            auto& pos = it->position;
            const auto row = pos.row;
            pos.row = pos.column;
            pos.column = side - row;
        }
    
    m_tileRenderer->setTilePositions(m_positions);
}
