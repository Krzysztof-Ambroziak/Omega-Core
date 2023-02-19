/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "SquaredTileCutter.hpp"

ld::SquaredTileCutter& ld::SquaredTileCutter::instance(const QSize& size, const QImage& image) {
    static SquaredTileCutter cutter;
    cutter.m_size = size;
    cutter.m_image = image;
    return cutter;
}

QImage ld::SquaredTileCutter::copy(const Position& position, const QColor& color) const {
    const QRect boundsSubimage(position.column * m_size.width(),
                               position.row * m_size.height(),
                               m_size.width(),
                               m_size.height());
    if(m_image.rect().contains(boundsSubimage))
        return m_image.copy(boundsSubimage);
    
    QImage image(m_size, QImage::Format_RGB32);
    image.fill(color);
    return image;
}
