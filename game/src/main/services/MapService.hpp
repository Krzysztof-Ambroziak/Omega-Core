/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef MAPSERVICE_HPP
#define MAPSERVICE_HPP

#include <QVector>

#include "loader/Map.hpp"
#include "loader/SpriteSheet.hpp"

class MapModel;
class AssetsModel;

class MapService {
    struct TileFiles {
        QString definition;
        QString tilesheet;
    };
    
    static constexpr auto L_MAP_COMPARATOR = [](const auto& a,
                                                const auto& b) -> bool { return a.name() < b.name(); };

public:
    MapService(AssetsModel* assetsModel, MapModel* mapModel);
    
    void loadTiles();
    
    void loadSpriteSheet(const QString& definitionFilename,
                         const QString& imageFileName);
    
    void changeMap(const QString& mapName);
    
    ld::MapSize mapSize() const;

private:
    static void addMap(QVector<ld::Map>& maps, const ld::Map& map);

private:
    QVector<ld::Map> makeMapContainer();
    
    const ld::Map& findMap(const QString& name) const;

private:
    static const QVector<TileFiles> TILE_FILES;
    static const QVector<QString> MAP_FILES;
    
    const QVector<ld::Map> m_maps;
    
    ld::SpriteSheet m_spriteSheets;
    
    AssetsModel* const m_assetsModel;
    
    MapModel* const m_mapModel;
};

inline const QVector<MapService::TileFiles> MapService::TILE_FILES {{ "tiles/xml/background-tile.xml", "tiles/images/background-tile.png" }};
inline const QVector<QString> MapService::MAP_FILES { "maps/start-map.xml" };

#endif  // MAPSERVICE_HPP
