/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "TileLoader.hpp"
#include "../../include/loader/TileSheet.hpp"
#include "utilities/IsometricTileCutter.hpp"
#include "utilities/NullTileCutter.hpp"
#include "utilities/SquaredTileCutter.hpp"

ld::TileLoader::TileLoader(const QString& def, const QImage& image) :
        m_reader(def),
        m_image(image) {}

ld::TileSheet ld::TileLoader::loadTiles() {
    static const ld::TileSheet& S_NULL_TILESHEET = ld::TileSheet::NULL_TILESHEET;
    
    if(!m_reader.readNextStartElement() || m_reader.name() != ROOT)
        return S_NULL_TILESHEET;
    
    if(!m_reader.readNextStartElement() || m_reader.name() != HEADER)
        return S_NULL_TILESHEET;
    
    const TileHeader& header = readHeader();
    
    if(!m_reader.readNextStartElement() || m_reader.name() != TILES)
        return S_NULL_TILESHEET;
    
    const ld::ITileCutter& cutter = imageCutter(header);
    return readTiles(header.type, cutter, header.size);
}

ld::TileLoader::TileHeader ld::TileLoader::readHeader() {
    TileHeader header;
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        
        if(name == HEADER_TYPE)
            header.type = readTileType();
        if(name == HEADER_PACKED)
            header.packed = readTilePacked();
        if(name == HEADER_TILESIZE)
            header.size = readTileSize();
    }
    
    return header;
}

ld::TileType ld::TileLoader::readTileType() {
    const QString& tileTypeStr = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                                         .trimmed();
    
    if(tileTypeStr == "square")
        return TILE_TYPE_SQUARE;
    if(tileTypeStr == "isometric")
        return TILE_TYPE_ISOMETRIC;
    
    return TILE_TYPE_UNKNOWN;
}

ld::TilePacked ld::TileLoader::readTilePacked() {
    const QString& tileTypeStr = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                                         .trimmed();
    
    if(tileTypeStr == "unpacked")
        return TILE_PACKED_UNPACKED;
    if(tileTypeStr == "packed")
        return TILE_PACKED_PACKED;
    
    return TILE_PACKED_UNKNOWN;
}

QSize ld::TileLoader::readTileSize() {
    int width = 0;
    int height = 0;
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        const int value = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                                  .trimmed()
                                  .toInt();
        
        if(name == HEADER_TILESIZE_WIDTH)
            width = value;
        if(name == HEADER_TILESIZE_HEIGHT)
            height = value;
    }
    
    if(width <= 0 || height <= 0)
        return {};
    
    return {width, height};
}

ld::TileSheet ld::TileLoader::readTiles(TileType tileType,
                                        const ITileCutter& cutter,
                                        const QSize& tileSize) {
    ld::TileSheet tileSheet(tileType, tileSize);
    
    while(m_reader.readNextStartElement() && m_reader.name() == TILES_TILE_ENTITY) {
        const TileDefinition& tileDef = readTile();
        
        if(!tileDef)
            continue;
        
        QImage image = cutter.copy(tileDef.position, tileDef.color);
        tileSheet.addImage(image, tileDef.name);
    }
    
    return tileSheet;
}

ld::TileLoader::TileDefinition ld::TileLoader::readTile() {
    QString tileName;
    ld::Position position;
    QColor color = Qt::black;
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        
        if(name == TILE_NAME)
            tileName = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                               .trimmed();
        if(name == TILE_POSITION)
            position = readPosition();
        if(name == TILE_ALTERNATIVE)
            color = readColor();
    }
    
    return {tileName, position, color};
}

ld::Position ld::TileLoader::readPosition() {
    ld::Position position;
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        const int value = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                                  .trimmed()
                                  .toInt();
        
        if(name == TILE_POS_ROW)
            position.row = value;
        if(name == TILE_POS_COL)
            position.column = value;
    }
    
    return position;
}

QColor ld::TileLoader::readColor() {
    QColor color;
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        const int value = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                                  .trimmed()
                                  .toInt();
        
        if(name == TILE_COLOR_RED)
            color.setRed(value);
        if(name == TILE_COLOR_GREEN)
            color.setGreen(value);
        if(name == TILE_COLOR_BLUE)
            color.setBlue(value);
    }
    
    return color;
}

const ld::ITileCutter& ld::TileLoader::imageCutter(const TileHeader& header) const {
    switch(header.type) {
    case TILE_TYPE_SQUARE:
        return SquaredTileCutter::instance(header.size, m_image);
    case TILE_TYPE_ISOMETRIC:
        return IsometricTileCutter::instance(header.size, header.packed, m_image);
    default:
        return NullTileCutter::instance();
    }
}
