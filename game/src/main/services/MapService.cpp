/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "MapService.hpp"

#include "loader/Loader.hpp"
#include "loader/TileSheet.hpp"
#include "loader/Map.hpp"

#include <QPixmap>

MapService::MapService(MapModel* model) : m_mapModel(model) {}

void MapService::loadTileSheet(const QString& def, const QString& img) {
    const ld::TileSheet& tileSheet = ld::Loader::loadTiles(def, img);

    for(const QString& key : tileSheet.keys()) {
        const QImage& image = tileSheet.image(key);
        if(!key.isEmpty() && !image.size().isEmpty())
            m_tileSheets += {key, new QPixmap(QPixmap::fromImage(image))};
    }

    std::sort(m_tileSheets.begin(),
              m_tileSheets.end(),
              [](const PTile& a, const PTile& b) { return a.name < b.name; });
}

void MapService::loadMap(const QString& filename) {
    const ld::Map& map = ld::Loader::loadMap(filename);
    const int size = m_maps.size();

    int index = 0;
    while(index < m_maps.size() && map.name() > m_maps[index]->name())
        index++;

    if(index >= size || map.name() != m_maps[index]->name())
        m_maps.insert(index, std::make_shared<ld::Map>(map));
}

void MapService::changeMap(const QString& mapName) {
    std::shared_ptr<ld::Map> map;

    const QVector<std::shared_ptr<ld::Map>> mm(m_maps);
    for(const std::shared_ptr<ld::Map>& m : mm)
        if(mapName == m->name())
            map = m;
    if(map == nullptr)
        return;

    m_mapModel->setMapSize(map->size());
    int i = 0;
    for(int row = 0; row < map->size().rows; row++)
        for(int column = 0; column < map->size().columns; column++) {
            const ld::Position pos{column, row};
            const QString& name = map->tile(pos);

            for(const PTile& tile : m_tileSheets)
                if(name == tile.name) {
                    m_mapModel->addTile(pos, *tile.image);
                    break;
                }
        }
}

MapService::~MapService() {
    for(const PTile& tile : m_tileSheets)
        delete tile.image;
}
