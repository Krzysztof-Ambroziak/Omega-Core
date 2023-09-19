/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "MapService.hpp"
#include "../models/AssetsModel.hpp"
#include "../models/MapModel.hpp"

#include "loader/Loader.hpp"
#include "loader/Map.hpp"

MapService::MapService(AssetsModel* assetsModel,
                       MapModel* mapModel) :
        m_maps(makeMapContainer()),
        m_assetsModel(assetsModel),
        m_mapModel(mapModel) {
    loadTiles();
}

void MapService::loadTiles() {
    foreach (const auto& tileFile, TILE_FILES) {
        foreach(const auto& tile, ld::Loader::loadTiles(":/" + tileFile.definition,
                                                        ":/" + tileFile.tilesheet)) {
            m_assetsModel->addTile(tile);
        }
    }
}

void MapService::loadSpriteSheet(const QString& def, const QString& img) {
    m_spriteSheets = ld::Loader::loadSprites(def, img);
}

void MapService::changeMap(const QString& mapName) {
    const auto& map = findMap(mapName);
    if(map == ld::Map::NULL_MAP)
        return;
    
    const ld::MapSize& mapSize = map.size();
    m_mapModel->setMapSize(mapSize);
    
    for(int row = 0; row < mapSize.rows; row++)
        for(int column = 0; column < mapSize.columns; column++) {
            const ld::Position& pos {column, row};
            const auto& tile = m_assetsModel->tile(map.tile(pos));
            
            m_mapModel->addTile(pos, tile);
        }
}

ld::MapSize MapService::mapSize() const {
    return m_mapModel->mapSize();
}

void MapService::addMap(QVector<ld::Map>& maps, const ld::Map& map) {
    const auto begin = maps.begin();
    const auto end = maps.end();
    const auto it = std::lower_bound<>(begin, end, map, L_MAP_COMPARATOR);
    
    if(it < end && map.name() == it->name())
        *it = map;
    else
        maps.insert(it, map);
}

QVector<ld::Map> MapService::makeMapContainer() {
    QVector<ld::Map> maps;
    
    foreach(const auto& filename, MAP_FILES) {
        const auto& map = ld::Loader::loadMap(":/" + filename);
        
        if(ld::Map::NULL_MAP != map)
            addMap(maps, map);
    }
    
    return maps;
}

const ld::Map& MapService::findMap(const QString& name) const {
    static auto map = ld::Map::NULL_MAP;
    map.setName(name);
    const auto cbegin = m_maps.cbegin();
    const auto cend = m_maps.cend();
    const auto it = std::lower_bound<>(cbegin, cend, map, L_MAP_COMPARATOR);
    
    if(it < cend && name == it->name())
        return *it;
    
    return map;
}
