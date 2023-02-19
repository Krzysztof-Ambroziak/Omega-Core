/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "TileCutterAdapter.hpp"

QSize ld::TileCutterAdapter::size() const {
    return m_size;
}

void ld::TileCutterAdapter::setSize(const QSize& size) {
    m_size = size;
}

QImage ld::TileCutterAdapter::image() const {
    return m_image;
}

void ld::TileCutterAdapter::setImage(const QImage& image) {
    m_image = image;
}
