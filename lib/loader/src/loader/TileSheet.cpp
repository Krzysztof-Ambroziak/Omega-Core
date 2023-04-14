/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <algorithm>  /* std::lower_bound */

#include "../../include/loader/TileSheet.hpp"
#include "utilities/PrivateHelpers.hpp"

ld::TileSheet::TileSheet() :
        m_tileType(ld::TileType::TILE_TYPE_UNKNOWN) {}

ld::TileSheet::TileSheet(ld::TileType tileType, const QSize& tileSize) :
        m_tileType(tileType),
        m_tileSize(tileSize) {}

ld::TileType ld::TileSheet::tileType() const {
    return m_tileType;
}

void ld::TileSheet::setTileType(TileType tileType) {
    m_tileType = tileType;
}

QSize ld::TileSheet::tileSize() const {
    return m_tileSize;
}

void ld::TileSheet::setTileSize(const QSize& tileSize) {
    m_tileSize = tileSize;
}

const QPixmap& ld::TileSheet::image(const QString& name) const {
    static NamedImage emptyNamedImage;
    emptyNamedImage.name = name;
    const auto& it = std::lower_bound<>(m_images.cbegin(),
                                        m_images.cend(),
                                        emptyNamedImage,
                                        L_COMPARATOR);
    
    if(it < m_images.cend() && name == it->name)
        return it->image;
    
    return emptyNamedImage.image;
}

void ld::TileSheet::addImage(const QPixmap& image,
                             const QString& name,
                             bool* repleace) {
    const NamedImage& newNamedImage {name, image};
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
