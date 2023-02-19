/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_DEFINITIONS_HPP
#define LD_DEFINITIONS_HPP

namespace ld {
enum TilePacked { TILE_PACKED_UNPACKED, TILE_PACKED_PACKED, TILE_PACKED_UNKNOWN };

struct Position {
    int column = -1;
    int row = -1;
};
}  // namespace ld

#endif  // LD_DEFINITIONS_HPP
