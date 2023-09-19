/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "../include/loader/Map.hpp"
#include "utilities/PrivateHelpers.hpp"

ld::Map::Map(const QString& name, const MapSize& size) :
        m_name(name),
        m_size(size),
        m_tiles(size.columns * size.rows) {}

QString ld::Map::name() const {
    return m_name;
}

void ld::Map::setName(const QString& name) {
    m_name = name;
}

ld::MapSize ld::Map::size() const {
    return m_size;
}

void ld::Map::setSize(const MapSize& size) {
    m_size = size;
    m_tiles.resize(m_size.rows * m_size.columns);
}

QString ld::Map::tile(const Position& position) const {
    return m_tiles[pos2ind(position)];
}

void ld::Map::addTile(const Position& position, const QString& tileName, bool* ok) {
    if(int index = pos2ind(position) ;
            index >= 0 && index < m_tiles.size() && m_tiles[index] != tileName) {
        m_tiles[index] = tileName;
        ld::setPVar<>(true, ok);
    }
    else
        ld::setPVar<>(false, ok);
}

bool ld::Map::operator==(const Map& map) const {
    if(this == &map)
        return true;
    
    const int tileSize = m_tiles.size();
    const auto& mapTiles = map.m_tiles;
    const auto& mapSize = map.m_size;
    if(m_size.rows != mapSize.rows ||
            m_size.columns != mapSize.columns ||
            tileSize != mapTiles.size())
        return false;
    
    for(int i = 0; i < tileSize; i++)
        if(m_tiles[i] != mapTiles[i])
            return false;
    
    return true;
}

bool ld::Map::operator!=(const Map& map) const {
    return !(*this == (map));
}

int ld::Map::pos2ind(const Position& position) const {
    return position.row * m_size.columns + position.column;
}
