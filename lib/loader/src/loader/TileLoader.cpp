/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "TileLoader.hpp"
#include "utilities/IsometricTileCutter.hpp"
#include "utilities/NullTileCutter.hpp"
#include "utilities/SquaredTileCutter.hpp"
#include "utilities/PrivateHelpers.hpp"

ld::TileLoader::TileLoader(const QString& def, const QImage& image) :
        m_reader(def),
        m_image(image) {}

QVector<ld::Tile> ld::TileLoader::loadTiles() {
    static const QVector<ld::Tile> EMPTY_CONTAINER;
    
    if(!m_reader.readNextStartElement() || m_reader.name() != ROOT)
        return EMPTY_CONTAINER;
    
    if(!m_reader.readNextStartElement() || m_reader.name() != HEADER)
        return EMPTY_CONTAINER;
    const TileHeader& header = readHeader();
    
    if(!m_reader.readNextStartElement() || m_reader.name() != TILES)
        return EMPTY_CONTAINER;
    
    const ld::ITileCutter& cutter = imageCutter(header);
    const auto& tileDefinitions = readTiles();
    
    QVector<ld::Tile> tiles;
    foreach (const auto& tileDef, tileDefinitions) {
        const auto& image = cutter.copy(tileDef.position, tileDef.color);
        tiles.push_back({tileDef.name, QPixmap::fromImage(image)});
    }
    
    return tiles;
}

ld::TileLoader::TileHeader ld::TileLoader::readHeader() {
    TileHeader header;
    const QStringRef& tagName = m_reader.name();
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        
        if(name == HEADER_TYPE)
            header.type = readTileType();
        if(name == HEADER_PACKED)
            header.packed = readTilePacked();
        if(name == HEADER_TILESIZE)
            header.size = readTileSize();
    }
    exitTag(tagName, m_reader);
    
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

QVector<ld::TileLoader::TileDefinition> ld::TileLoader::readTiles() {
    QVector<TileDefinition> tiles;
    
    while(m_reader.readNextStartElement() && m_reader.name() == TILES_TILE_ENTITY) {
        const TileDefinition& tileDef = readTile();
        
        if(!tileDef)
            continue;
        tiles += tileDef;
    }
    
    return tiles;
}

ld::TileLoader::TileDefinition ld::TileLoader::readTile() {
    QString tileName;
    ld::Position position;
    QColor color = Qt::black;
    const QStringRef& tagName = m_reader.name();
    
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
    exitTag(tagName, m_reader);
    
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
    const QStringRef& tagName = m_reader.name();
    
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
    exitTag(tagName, m_reader);
    
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
