/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <QFile>
#include <QImage>

#include "../../include/loader/Loader.hpp"
#include "../../include/loader/TileSheet.hpp"
#include "TileLoader.hpp"

ld::TileSheet ld::Loader::loadTiles(const QString& defFilename, const QString& image) {
    const QString& def = readFile(defFilename);
    const QImage img(image);
    
    return TileLoader(def, img).loadTiles();
}

QByteArray ld::Loader::readFile(const QString& filename) {
    QByteArray array;
    
    if(QFile file(filename) ; file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        array = file.readAll();
        file.close();
    }
    
    return array;
}
