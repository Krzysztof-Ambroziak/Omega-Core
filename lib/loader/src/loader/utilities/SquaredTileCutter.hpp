/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_SQUARETILECUTTER_HPP
#define LD_SQUARETILECUTTER_HPP

#include "TileCutterAdapter.hpp"

namespace ld {
class SquaredTileCutter : public TileCutterAdapter {
public:
    static SquaredTileCutter& instance(const QSize& size, const QImage& image);

public:
    SquaredTileCutter(const SquaredTileCutter& cutter) = delete;
    
    QImage copy(const Position& position, const QColor& color) const override;

private:
    SquaredTileCutter() = default;
};
}  // namespace ld

#endif  // LD_SQUARETILECUTTER_HPP
