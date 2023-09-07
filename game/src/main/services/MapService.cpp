/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <QPixmap>

#include "MapService.hpp"
#include "../models/MapModel.hpp"

#include "loader/Loader.hpp"
#include "loader/Map.hpp"

MapService::MapService(MapModel* model) : m_mapModel(model) {}

void MapService::loadTileSheet(const QString& def, const QString& img) {
    m_tileSheet = ld::Loader::loadTiles(def, img);
}

void MapService::loadSpriteSheet(const QString& def, const QString& img) {
    m_spriteSheets = ld::Loader::loadSprites(def, img);
}

void MapService::loadMap(const QString& filename) {
    QString name;
    const ld::Map& map = ld::Loader::loadMap(filename, name);
    m_mapSheet.addMap(map, name);
}

void MapService::changeMap(const QString& mapName) {
    struct NamedImage {
        QString name;
        QPixmap* image;
    };
    
    const auto& map = m_mapSheet.map(mapName);
    if(map == ld::Map::NULL_MAP)
        return;
    
    const ld::MapSize& mapSize = map.size();
    QVector<NamedImage> images;
    
    m_mapModel->setMapSize(mapSize);
    
    for(int row = 0; row < mapSize.rows; row++)
        for(int column = 0; column < mapSize.columns; column++) {
            const ld::Position& pos{column, row};
            const QString& name = map.tile(pos);
            NamedImage image{name, nullptr};
            
            if(auto it = std::lower_bound(images.begin(),
                                          images.end(),
                                          image,
                                          [](const auto&a, const auto& b) { return a.name < b.name; }) ;
                    it < images.end() && it->name == name)
                image.image = it->image;
            else
                image.image = new QPixmap(m_tileSheet.image(image.name));
            
            m_mapModel->addTile(pos, *image.image);
        }
}

ld::MapSize MapService::mapSize() const {
    return m_mapModel->mapSize();
}
