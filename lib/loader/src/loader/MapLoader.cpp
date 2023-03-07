/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "MapLoader.hpp"
#include "loader/Map.hpp"

void ld::MapLoader::copyRawTilesToMap(Map& target,
                                      const RawTileEntity& tileEntity) {
    ld::Position position = tileEntity.position;
    const int columns = target.size().columns;
    
    for(int i = 0; i < tileEntity.multiplier; i++, position.column++) {
        if(position.column == columns) {
            position.row++;
            position.column = 0;
        }
        target.addTile(position, tileEntity.name);
    }
}

ld::MapLoader::MapLoader(const QString& mapFile) :
        m_reader(mapFile) {}

ld::Map ld::MapLoader::loadMap() {
    static const ld::Map& S_NULL_MAP = ld::Map::NULL_MAP;
    
    if(!m_reader.readNextStartElement() || m_reader.name() != ROOT)
        return S_NULL_MAP;
    
    if(!m_reader.readNextStartElement() || m_reader.name() != HEADER)
        return S_NULL_MAP;
    const MapHeader& header = readHeader();
    
    if(header.size.rows != header.size.columns)
        return S_NULL_MAP;
    
    ld::Map map = readLayers(header.size);
    map.addTileNamespaces(header.tileNamespaces);
    
    return map;
}

ld::MapLoader::MapHeader ld::MapLoader::readHeader() {
    MapHeader header;
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        
        if(name == HEADER_MAP_NAME)
            header.name = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                                  .trimmed();
        if(name == HEADER_MAP_SIZE)
            header.size = readMapSize();
        if(name == HEADER_TILE_NAMESPACES)
            header.tileNamespaces = readTileNamespaces();
    }
    
    return header;
}

ld::MapSize ld::MapLoader::readMapSize() {
    MapSize size;
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        const int value = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                                  .trimmed()
                                  .toInt();
        
        if(name == HEADER_MAP_ROWS)
            size.rows = value;
        if(name == HEADER_MAP_COLUMNS)
            size.columns = value;
    }
    
    return size;
}

QStringList ld::MapLoader::readTileNamespaces() {
    QStringList namespaces;
    
    while(m_reader.readNextStartElement()) {
        if(m_reader.name() == HEADER_TILE_NAMESPACE)
            if(const QString& tileNamespace =
                    m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                    .trimmed() ; !tileNamespace.isEmpty())
                namespaces += tileNamespace;
        }
    
    return namespaces;
}

ld::Map ld::MapLoader::readLayers(const MapSize& mapSize) {
    if(!m_reader.readNextStartElement() || m_reader.name() != LAYERS)
        return ld::Map::NULL_MAP;
    
    Map map(mapSize);
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        
        if(name == TILE_LAYER)
            readTiles(map);
        if(name == SPRITE_LAYER)
            m_reader.skipCurrentElement();
        if(name == OBJECT_LAYER)
            m_reader.skipCurrentElement();
    }
    
    return map;
}

void ld::MapLoader::readTiles(Map& map) {
    while(m_reader.readNextStartElement() && m_reader.name() == TILE_LAYER_TILE_ENTITY) {
        const RawTileEntity& entity = readRawTileEntity();
        
        if(!entity)
            continue;
        copyRawTilesToMap(map, entity);
    };
}

//void ld::MapLoader::readSprites() {}

//void ld::MapLoader::readObjects() {}

ld::MapLoader::RawTileEntity ld::MapLoader::readRawTileEntity() {
    ld::MapLoader::RawTileEntity entity;
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        const QString& value = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                                       .trimmed();
        
        if(name == TILE_ENTITY_ROW)
            entity.position.row = value.toInt();
        if(name == TILE_ENTITY_COLUMN)
            entity.position.column = value.toInt();
        if(name == TILE_ENTITY_MULTIPLIER)
            entity.multiplier  = value.toInt();
        if(name == TILE_ENTITY_TILE_NAME)
            entity.name = value;
    }
    
    return entity;
}
