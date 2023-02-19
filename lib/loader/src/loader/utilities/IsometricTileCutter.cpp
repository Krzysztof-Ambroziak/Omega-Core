/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "IsometricTileCutter.hpp"

#include <QPainter>

ld::IsometricTileCutter& ld::IsometricTileCutter::instance(const QSize& size,
                                                           const TilePacked& packed,
                                                           const QImage& image) {
    static IsometricTileCutter cutter;
    if(cutter.m_size != size) {
        cutter.m_size = size;
        cutter.makeMask();
    }
    cutter.m_packed = packed;
    cutter.m_image = image;
    return cutter;
}

QImage ld::IsometricTileCutter::copy(const Position& position,
                                     const QColor& color) const {
    QImage image(m_size, QImage::Format_ARGB32);
    const QRect& bound = boundSubimage(position);
    
    if(m_image.rect().contains(bound)) {
        switch(m_packed) {
        case TILE_PACKED_PACKED:
            unpackImage(image, m_image.copy(bound));
            break;
        case TILE_PACKED_UNPACKED:
            copyImage(image, m_image.copy(bound));
            break;
        default: {}  // no action
        }
    }
    else
        image.fill(color);
    
    image.setAlphaChannel(m_alphaMask);
    
    return image;
}

QRect ld::IsometricTileCutter::boundSubimage(const Position& position) const {
    const int width = m_packed == TilePacked::TILE_PACKED_PACKED ? m_size.width() / 2 : m_size.width();
    const int height = m_packed == TilePacked::TILE_PACKED_PACKED ? m_size.height() + 2 : m_size.height();
    const int x = position.column * width;
    const int y = position.row * height;
    
    return QRect(x, y, width, height);
}

void ld::IsometricTileCutter::unpackImage(QImage& target, const QImage& source) const {
    const int halfWidth = m_size.width() / 2;
    const int halfHeight = m_size.height() / 2;
    
    QPainter painter;
    painter.begin(&target);
    painter.drawImage(0, 0, source.copy(0, 1, halfWidth, m_size.height()));
    painter.drawImage(halfWidth, 0,          source.copy(0, halfHeight + 2, halfWidth, halfHeight));
    painter.drawImage(halfWidth, halfHeight, source.copy(0, 0, halfWidth, halfHeight));
    painter.end();
}

void ld::IsometricTileCutter::copyImage(QImage& target,
                                        const QImage& source) const {
    QPainter painter;
    painter.begin(&target);
    painter.drawImage(0, 0, source);
    painter.end();
}

void ld::IsometricTileCutter::makeMask() {
    m_alphaMask = QImage(m_size, QImage::Format_Alpha8);
    m_alphaMask.fill(Qt::transparent);
    const int halfHeight = m_size.height() / 2;
    const int halfWidth = m_size.width() / 2;
    
    // top-right quarter
    QImage triangleMask(halfWidth, halfHeight, QImage::Format_Alpha8);
    triangleMask.fill(Qt::transparent);
    for(int y = 0; y < halfHeight; y++) {
        auto rawData = triangleMask.scanLine(y);
        for(int x = 0; x < 2*y + 2; x++)
            rawData[x] = 0xff;  // set opaque (alpha channel = 255)
    }
    
    QPainter painter;
    painter.begin(&m_alphaMask);
    painter.drawImage(halfWidth, 0, triangleMask);  // top-right
    painter.drawImage(0, 0, triangleMask.mirrored(true, false));  // top-left
    painter.drawImage(0, halfHeight , triangleMask.mirrored(true, true));  // bottom-left
    painter.drawImage(halfWidth, halfHeight, triangleMask.mirrored(false, true));  // bottom-right
    painter.end();
}
