/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_TILECUTTERADAPTER_HPP
#define LD_TILECUTTERADAPTER_HPP

#include "api/ITileCutter.hpp"

namespace ld {
class TileCutterAdapter : public ITileCutter {
public:
    QSize size() const;
    void setSize(const QSize& size);
    
    QImage image() const;
    void setImage(const QImage& image);

protected:
    QSize m_size;
    
    QImage m_image;
};
}  // namespace ld

#endif  // LD_TILECUTTERADAPTER_HPP
