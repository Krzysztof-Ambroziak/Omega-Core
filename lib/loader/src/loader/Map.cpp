/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "../include/loader/Map.hpp"
#include "utilities/PrivateHelpers.hpp"

ld::Map::Map(const QString& name, const MapSize& size, const QStringList& tileNamespaces) :
        m_name(name),
        m_size(size),
        m_namespaces(tileNamespaces),
        m_tiles(size.columns * size.rows) {}

QString ld::Map::name() const {
    return m_name;
}

ld::MapSize ld::Map::size() const {
    return m_size;
}

QStringList ld::Map::tileNamespaces() const {
    return m_namespaces;
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

int ld::Map::pos2ind(const Position& position) const {
    return position.row * m_size.columns + position.column;
}
