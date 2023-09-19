/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "AssetsModel.hpp"

void AssetsModel::addTile(const ld::Tile& tile) {
    const auto begin = m_tiles.begin();
    const auto end = m_tiles.end();
    const auto it = std::lower_bound<>(begin, end, tile, L_TILE_COMPARATOR);
    
    if(it < end && tile.name == it->name)
        it->image = tile.image;
    else
        m_tiles.insert(it, tile);
}

const QPixmap& AssetsModel::tile(const QString& name) const {
    static ld::Tile emptyTile {{}, {}};
    emptyTile.name = name;
    const auto cbegin = m_tiles.cbegin();
    const auto cend = m_tiles.cend();
    const auto it = std::lower_bound<>(cbegin, cend, emptyTile, L_TILE_COMPARATOR);
    
    if(it < cend && name == it->name)
        return it->image;
    
    return emptyTile.image;
}
