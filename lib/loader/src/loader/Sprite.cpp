/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "../../include/loader/Sprite.hpp"

QPoint ld::Sprite::pivot() const {
    return m_pivot;
}

void ld::Sprite::setPivot(QPoint pivot) {
    m_pivot = pivot;
}

const QPixmap& ld::Sprite::image(int index) const {
    return m_images[index];
}

void ld::Sprite::addImage(const QPixmap& pixmap) {
    m_images += pixmap;
}

void ld::Sprite::addImages(const QVector<QPixmap>& pixmaps) {
    m_images += pixmaps;
}

int ld::Sprite::size() const {
    return m_images.size();
}
