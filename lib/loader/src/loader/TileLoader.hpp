/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_TILELOADER_HPP
#define LD_TILELOADER_HPP

#include <QImage>
#include <QXmlStreamReader>

#include "Definitions.hpp"
#include "../../include/Commons.hpp"

class QSize;

namespace ld {
class TileSheet;
class ITileCutter;

class TileLoader {
private:
    struct TileHeader {
        QString namesp;
        QSize size;
        TileType type;
        TilePacked packed;
    };
    
    struct TileDefinition {
        const QString name;
        const Position position;
        const QColor color;
        
        operator bool() const {
            return !name.isEmpty() && position.row >= 0 && position.column >= 0;
        }
    };

public:
    TileLoader(const QString& defFilename, const QImage& image);
    
    TileSheet loadTiles();

private:
    TileHeader readHeader();
    
    TileType readTileType();
    
    TilePacked readTilePacked();
    
    QSize readTileSize();
    
    TileSheet readTiles(const QString& namesp,
                        TileType tileType,
                        const ITileCutter& cutter,
                        const QSize& tileSize);
    
    TileDefinition readTile();
    
    Position readPosition();
    
    QColor readColor();
    
    QImage subimage() const;
    
    const ITileCutter& imageCutter(const TileHeader& header) const;

private:
    QXmlStreamReader m_reader;
    
    QImage m_image;

private:
    inline static const QString ROOT = "tileset";
    inline static const QString HEADER = "header";
    inline static const QString TILES = "tiles";
    inline static const QString HEADER_NAMESPACE = "namespace";
    inline static const QString HEADER_TYPE = "type";
    inline static const QString HEADER_PACKED = "packed";
    inline static const QString HEADER_TILESIZE = "tilesize";
    inline static const QString HEADER_TILESIZE_WIDTH = "width";
    inline static const QString HEADER_TILESIZE_HEIGHT = "height";
    inline static const QString TILES_TILE_ENTITY = "tile";
    inline static const QString TILE_NAME = "name";
    inline static const QString TILE_POSITION = "position";
    inline static const QString TILE_ALTERNATIVE = "alternative";
    inline static const QString TILE_POS_ROW = "row";
    inline static const QString TILE_POS_COL = "column";
    inline static const QString TILE_COLOR_RED = "r";
    inline static const QString TILE_COLOR_GREEN = "g";
    inline static const QString TILE_COLOR_BLUE = "b";
};
}  // namespace ld

#endif  // LD_TILELOADER_HPP
