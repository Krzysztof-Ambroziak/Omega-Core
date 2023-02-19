/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_ISOMETRICTILECUTTER_HPP
#define LD_ISOMETRICTILECUTTER_HPP

#include "TileCutterAdapter.hpp"

namespace ld {
class IsometricTileCutter : public TileCutterAdapter {
private:
    enum MaskTriangle { TOP_RIGHT, TOP_LEFT, BOTTOM_LEFT, BOTTOM_RIGHT };

public:
    static IsometricTileCutter& instance(const QSize& size,
                                         const TilePacked& packed,
                                         const QImage& image);

public:
    IsometricTileCutter(const IsometricTileCutter& cutter) = delete;
    
    QImage copy(const Position& position, const QColor& color) const override;

private:
    IsometricTileCutter() = default;
    
    QRect boundSubimage(const Position& position) const;
    
    void unpackImage(QImage& target, const QImage& source) const;
    
    void copyImage(QImage& target, const QImage& source) const;
    
    void makeMask();

private:
    TilePacked m_packed;
    
    QImage m_alphaMask;
};
}  // namespace ld

#endif  // LD_ISOMETRICTILECUTTER_HPP
