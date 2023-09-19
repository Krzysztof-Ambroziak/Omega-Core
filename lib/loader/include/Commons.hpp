/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_COMMONS_HPP
#define LD_COMMONS_HPP

#include <QPixmap>

namespace ld {
struct Position {
    int column = -1;
    int row = -1;
};

struct MapSize {
    int columns = -1;
    int rows = -1;
};

enum TileType { TILE_TYPE_UNKNOWN, TILE_TYPE_SQUARE, TILE_TYPE_ISOMETRIC };

struct Tile {
    QString name;
    QPixmap image;
};

}  // namespace ld

#endif  // LD_COMMONS_HPP
