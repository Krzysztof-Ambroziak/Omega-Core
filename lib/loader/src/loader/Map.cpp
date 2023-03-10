/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "../include/loader/Map.hpp"
#include "utilities/PrivateHelpers.hpp"

ld::Map::Map(const MapSize& size, const QString& name) :
        m_size(size),
        m_name(name),
        m_tiles(size.columns * size.rows) {}

ld::MapSize ld::Map::size() const {
    return m_size;
}

QString ld::Map::name() const {
    return m_name;
}

QString ld::Map::tile(const Position& position) const {
    return m_tiles[indexFromPosition(position)];
}

void ld::Map::addTile(const Position& position, const QString& tileName, bool* ok) {
    if(int index = indexFromPosition(position) ;
            index >= 0 && index < m_tiles.size() && m_tiles[index] != tileName) {
        m_tiles[index] = tileName;
        ld::setPVar<>(true, ok);
    }
    else
        ld::setPVar<>(false, ok);
}

int ld::Map::indexFromPosition(const Position& position) const {
    return position.row * m_size.columns + position.column;
}
