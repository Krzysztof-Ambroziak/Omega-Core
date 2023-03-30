/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <memory>

#include <QPixmap>

#include "MapService.hpp"
#include "../models/MapModel.hpp"

#include "loader/Loader.hpp"
#include "loader/Map.hpp"
#include "loader/Sprite.hpp"

MapService::MapService(MapModel* model) : m_mapModel(model) {}

void MapService::loadTileSheet(const QString& def, const QString& img) {
    m_tileSheet = ld::Loader::loadTiles(def, img);
}

void MapService::loadSpriteSheet(const QString& def,
                                 const QString& img) {
    const auto& sprites = ld::Loader::loadSprite(def, img);
    
    foreach(const auto& sprite, sprites) {
        m_spriteSheets += std::make_shared<ld::Sprite>(sprite);
    }
}

void MapService::loadMap(const QString& filename) {
    const ld::Map& newMap = ld::Loader::loadMap(filename);
    
    if(!newMap.name().isEmpty()) {
        const auto& map = std::make_shared<ld::Map>(newMap);
        const auto& it = std::lower_bound(m_maps.begin(),
                                          m_maps.end(),
                                          map,
                                          [](const auto& a, const auto& b) { return a->name() < b->name(); });
        m_maps.insert(it, map);
    }
}

void MapService::changeMap(const QString& mapName) {
    struct NamedImage {
        QString name;
        QPixmap* image;
    };
    
    const auto& map = findMap(mapName);
    if(map == nullptr)
        return;
    
    const ld::MapSize& mapSize = map->size();
    QVector<NamedImage> images;
    
    m_mapModel->setMapSize(mapSize);
    
    for(int row = 0; row < mapSize.rows; row++)
        for(int column = 0; column < mapSize.columns; column++) {
            const ld::Position& pos{column, row};
            const QString& name = map->tile(pos);
            NamedImage image{name, nullptr};
            
            if(auto it = std::lower_bound(images.begin(),
                                          images.end(),
                                          image,
                                          [](const auto&a, const auto& b) { return a.name < b.name; }) ;
                    it < images.end() && it->name == name)
                image.image = it->image;
            else
                image.image = new QPixmap(QPixmap::fromImage(m_tileSheet.image(image.name)));
            
            m_mapModel->addTile(pos, image.image);
        }
}

std::shared_ptr<ld::Map> MapService::findMap(const QString& mapName) const {
    std::shared_ptr<ld::Map> map;
    
    foreach(const auto& m, m_maps)
        if(mapName == m->name()) {
            map = m;
            break;
        }
    
    return map;
}
