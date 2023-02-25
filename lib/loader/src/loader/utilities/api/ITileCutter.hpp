/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_ITILECUTTER_HPP
#define LD_ITILECUTTER_HPP

#include "../../../../include/Commons.hpp"

class QColor;
class QImage;

namespace ld {
class ITileCutter {
public:
    virtual QImage copy(const Position& position, const QColor& color) const = 0;
};
}  // namespace ld

#endif  // LD_ITILECUTTER_HPP
