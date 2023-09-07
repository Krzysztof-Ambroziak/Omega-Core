/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "MapModel.hpp"

#include <QPixmap>

const QPixmap& MapModel::tile(const ld::Position& position) const {
    return m_tiles[index(position)];
}

void MapModel::addTile(const ld::Position& position, const QPixmap& image) {
    m_tiles[index(position)] = image;
}

void MapModel::setMapSize(const ld::MapSize& mapSize) {
    m_mapSize = mapSize;
    m_tiles.fill(QPixmap(), m_mapSize.rows * m_mapSize.columns);
}

ld::MapSize MapModel::mapSize() const {
    return m_mapSize;
}

int MapModel::index(const ld::Position& position) const {
    return position.row * m_mapSize.columns + position.column;
}
