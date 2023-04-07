/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_LOADER_HPP
#define LD_LOADER_HPP

//#include "Sprite.hpp"

class QString;
class QByteArray;

namespace ld {
class Map;
class TileSheet;
class SpriteSheet;

class Loader {
public:
    static TileSheet loadTiles(const QString& definitionFilename,
                               const QString& imageFilename);
    
    static SpriteSheet loadSprites(const QString& definitionFilename,
                                   const QString& imageFilename);
    
    static Map loadMap(const QString& definitionFilename);

public:
    Loader() = delete;

private:
    static QByteArray readFile(const QString& filename);
};
}  // namespace ld

#endif  // LD_LOADER_HPP
