/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <QFile>
#include <QImage>

#include "../../include/loader/Loader.hpp"
#include "../../include/loader/Map.hpp"
#include "../../include/loader/TileSheet.hpp"
#include "MapLoader.hpp"
#include "SpriteLoader.hpp"
#include "TileLoader.hpp"

ld::TileSheet ld::Loader::loadTiles(const QString& sDef, const QString& sImg) {
    const QString& def = readFile(sDef);
    const QImage img(sImg);
    
    return TileLoader(def, img).loadTiles();
}

QVector<ld::Sprite> ld::Loader::loadSprite(const QString& sDef, const QString& sImg) {
    const QString& def = readFile(sDef);
    const QImage img(sImg);
    
    return SpriteLoader(def, img).loadSprites();
}

ld::Map ld::Loader::loadMap(const QString& sDef) {
    const QString& def = readFile(sDef);
    
    return MapLoader(def).loadMap();
}

QByteArray ld::Loader::readFile(const QString& filename) {
    QByteArray array;
    
    if(QFile file(filename) ; file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        array = file.readAll();
        file.close();
    }
    
    return array;
}
