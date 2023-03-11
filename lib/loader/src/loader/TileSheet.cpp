/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <algorithm>  /* std::lower_bound */

#include "../../include/loader/TileSheet.hpp"
#include "utilities/PrivateHelpers.hpp"

ld::TileSheet::TileSheet(ld::TileType tileType, const QSize& tileSize) :
        c_tileType(tileType),
        c_tileSize(tileSize) {}

void ld::TileSheet::addImage(const QImage& image, const QString& name, bool* repleace) {
    const NamedImage& newNamedImage {image, name};
    const auto& it = std::lower_bound<>(m_images.begin(),
                                        m_images.end(),
                                        newNamedImage,
                                        L_COMPARATOR);
    
    if(it < m_images.end() && name == it->name) {
        it->image = newNamedImage.image;
        ld::setPVar<>(true, repleace);
    }
    else {
        m_images.insert(it, newNamedImage);
        ld::setPVar<>(false, repleace);
    }
}

QStringList ld::TileSheet::keys() const {
    QStringList keys;
    
    for(const NamedImage& image : m_images)
        keys += image.name;
    
    return keys;
}

QImage ld::TileSheet::image(const QString& name) const {
    const NamedImage& emptyNamedImage {{}, name};
    const auto& it = std::lower_bound<>(m_images.cbegin(),
                                        m_images.cend(),
                                        emptyNamedImage,
                                        L_COMPARATOR);
    
    if(it < m_images.cend() && name == it->name)
        return it->image;
    
    return emptyNamedImage.image;
}

ld::TileType ld::TileSheet::tileType() const {
    return c_tileType;
}

QSize ld::TileSheet::tileSize() const {
    return c_tileSize;
}
