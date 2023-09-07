/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef MAPSERVICE_HPP
#define MAPSERVICE_HPP

#include <QVector>

#include "loader/MapSheet.hpp"
#include "loader/SpriteSheet.hpp"
#include "loader/TileSheet.hpp"

class MapModel;

class MapService {
public:
    MapService(MapModel* model);
    
    void loadTileSheet(const QString& definitionFilename,
                       const QString& imageFileName);
    
    void loadSpriteSheet(const QString& definitionFilename,
                         const QString& imageFileName);
    
    void loadMap(const QString& definitionFilename);
    
    void changeMap(const QString& mapName);
    
    ld::MapSize mapSize() const;

private:
    ld::TileSheet m_tileSheet;
    
    ld::SpriteSheet m_spriteSheets;
    
    ld::MapSheet m_mapSheet;
    
    MapModel* const m_mapModel;
};

#endif  // MAPSERVICE_HPP
