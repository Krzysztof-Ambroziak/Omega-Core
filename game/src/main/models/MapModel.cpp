/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "MapModel.hpp"

#include <QPixmap>

const QPixmap* MapModel::tile(const ld::Position& position) const {
    return m_tiles[position.row * m_mapSize.columns + position.column];
}

void MapModel::addTile(const ld::Position& position, const QPixmap& image) {
    m_tiles[index(position)] = new QPixmap(image);
}

void MapModel::setMapSize(const ld::MapSize& mapSize) {
    m_mapSize = mapSize;
    qDeleteAll(m_tiles);
    m_tiles.fill(nullptr, mapSize.rows * mapSize.columns);
}

int MapModel::index(const ld::Position& position) const {
    return position.row * m_mapSize.columns + position.column;
}
