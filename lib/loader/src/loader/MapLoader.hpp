/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_MAPLOADER_HPP
#define LD_MAPLOADER_HPP

#include <QXmlStreamReader>

#include "../../include/Commons.hpp"

namespace ld {
class Map;

class MapLoader {
private:
    struct MapHeader {
        QString name;
        MapSize size;
    };
    
    struct RawTileEntity {
        ld::Position position;
        int multiplier = 1;
        QString name;
        
        operator bool() const {
            return !name.isEmpty()
                    && multiplier >= 1
                    && position.row >= 0
                    && position.column >= 0;
        }
    };

private:
    static void copyRawTilesToMap(Map& target, const RawTileEntity& tileEntity);

public:
    MapLoader(const QString& mapFile);
    
    Map loadMap();

private:
    MapHeader readHeader();
    
    MapSize readMapSize();
    
    Map readLayers(const MapSize& mapSize, const QString& mapName);
    
    void readTiles(Map& map);
    
//    void readSprites();
    
//    void readObjects();
    
    RawTileEntity readRawTileEntity();

private:
    QXmlStreamReader m_reader;

private:
    inline static const QString ROOT = "map";
    inline static const QString HEADER = "header";
    inline static const QString HEADER_MAP_NAME = "name";
    inline static const QString HEADER_MAP_SIZE = "map-size";
    inline static const QString HEADER_MAP_ROWS = "rows";
    inline static const QString HEADER_MAP_COLUMNS = "columns";
    inline static const QString LAYERS = "layers";
    inline static const QString TILE_LAYER = "tile-layer";
    inline static const QString SPRITE_LAYER = "sprite-layer";
    inline static const QString OBJECT_LAYER = "object-layer";
    inline static const QString TILE_LAYER_TILE_ENTITY = "tile";
    inline static const QString TILE_ENTITY_ROW = "row";
    inline static const QString TILE_ENTITY_COLUMN = "col";
    inline static const QString TILE_ENTITY_MULTIPLIER = "multiplier";
    inline static const QString TILE_ENTITY_TILE_NAME = "name";
};
}  // namespace ld

#endif  // LD_MAPLOADER_HPP
