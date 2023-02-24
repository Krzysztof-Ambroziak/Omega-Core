/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_LOADER_HPP
#define LD_LOADER_HPP

class QString;
class QByteArray;

namespace ld {
class Map;
class TileSheet;

class Loader {
public:
    static TileSheet loadTiles(const QString& definitionFilename, const QString& imageFilename);
    
    static Map loadMap(const QString& definitionFilename);

private:
    static QByteArray readFile(const QString& filename);

public:
    Loader() = delete;
};
}  // namespace ld

#endif  // LD_LOADER_HPP
