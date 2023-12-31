/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef OCGLOBAL_HPP
#define OCGLOBAL_HPP

#include "Commons.hpp"

namespace oc {
enum DirectionOfRotation { DOR_CLOCKWISE, DOR_COUNTERCLOCKWISE };

enum Rotation { UNDEFINED_ROTATION, ROTATION_0_DEG, ROTATION_90_DEG, ROTATION_180_DEG, ROTATION_270_DEG };

struct Offset {
    int xOffset;
    int yOffset;
};

struct TilePosition {
    ld::Position position;
    Offset offset;
};
}  // namespace oc

#endif  // OCGLOBAL_HPP
