/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_LOADER_HPP
#define LD_LOADER_HPP

class QByteArray;
class QString;
template<class T>
class QVector;

namespace ld {
class Map;
struct Tile;
class SpriteSheet;

class Loader {
public:
    static QVector<ld::Tile> loadTiles(const QString& definitionFilename,
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
