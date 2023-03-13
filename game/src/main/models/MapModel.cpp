/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "MapModel.hpp"

const QPixmap* MapModel::tile(const ld::Position& position) const {
    return m_tiles[position.row * m_mapSize.columns + position.column];
}

void MapModel::addTile(const ld::Position& position, const QPixmap* const image) {
    m_tiles[index(position)] = image;
}

void MapModel::setMapSize(const ld::MapSize& mapSize) {
    m_mapSize = mapSize;
    m_tiles.fill(nullptr, mapSize.rows * mapSize.columns);
}

int MapModel::index(const ld::Position& position) const {
    return position.row * m_mapSize.columns + position.column;
}
