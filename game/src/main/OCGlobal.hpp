/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef OCGLOBAL_HPP
#define OCGLOBAL_HPP

namespace oc {
enum RendererType { NULL_RENDERER, TILE_RENDERER };

enum Rotation { ROTATION_0_DEG, ROTATION_90_DEG, ROTATION_180_DEG, ROTATION_270_DEG, UNDEFINED_ROTATION };

struct Offset {
    int xOffset;
    int yOffset;
};
}  // namespace oc

#endif  // OCGLOBAL_HPP
