/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <QFile>
#include <QImage>

#include "../../include/loader/Loader.hpp"
#include "../../include/loader/Map.hpp"
#include "../../include/loader/TileSheet.hpp"
#include "MapLoader.hpp"
#include "TileLoader.hpp"

ld::TileSheet ld::Loader::loadTiles(const QString& defFilename, const QString& image) {
    const QString& def = readFile(defFilename);
    const QImage img(image);
    
    return TileLoader(def, img).loadTiles();
}

ld::Map ld::Loader::loadMap(const QString& defFilename) {
    const QString& def = readFile(defFilename);
    
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
