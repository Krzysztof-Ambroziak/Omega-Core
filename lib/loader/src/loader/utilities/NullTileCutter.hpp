/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_NULLTILECUTTER_HPP
#define LD_NULLTILECUTTER_HPP

#include "api/ITileCutter.hpp"

#include <QImage>

namespace ld {
class NullTileCutter : public ITileCutter {
public:
    static NullTileCutter& instance();

public:
    NullTileCutter(const NullTileCutter& cutter) = delete;
    
    QImage copy(const Position& position, const QColor& color) const override;

private:
    NullTileCutter() = default;
};

inline NullTileCutter& NullTileCutter::instance() {
    static NullTileCutter cutter;
    return cutter;
}

inline QImage NullTileCutter::copy(const Position& position, const QColor& color) const {
    return QImage();
}
}  // namespace ld

#endif  // LD_NULLTILECUTTER_HPP
