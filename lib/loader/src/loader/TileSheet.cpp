/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "../../include/loader/TileSheet.hpp"
#include "utilities/PrivateHelpers.hpp"

ld::TileSheet::TileSheet(const QString& tileNamespace,
                         ld::TileType tileType,
                         const QSize& tileSize) :
        m_sheetNamespace(tileNamespace),
        m_tileType(tileType),
        m_tileSize(tileSize) {}

void ld::TileSheet::addImage(const QImage& image, const QString& name, bool* repleace) {
    const int end = m_images.size();
    const int index = binarySearchIndex(name);
    
    if(index < end && name == m_images[index].name) {
        ld::setPVar<>(true, repleace);
        m_images[index] = {image, name};
    }
    else {
        ld::setPVar<>(false, repleace);
        m_images.insert(index, {image, name});
    }
}

QString ld::TileSheet::sheetNamespace() const {
    return m_sheetNamespace;
}

QStringList ld::TileSheet::keys() const {
    QStringList keys;
    
    for(const NamedImage& image : m_images)
        keys += image.name;
    
    return keys;
}

QImage ld::TileSheet::image(const QString& name) const {
    const int index = binarySearchIndex(name);
    
    if(index < m_images.size() && name == m_images[index].name)
        return m_images[index].image;
    
    return {};
}

ld::TileType ld::TileSheet::tileType() const {
    return m_tileType;
}

int ld::TileSheet::binarySearchIndex(const QString& name) const {
    int start = 0;
    int end = m_images.size();
    
    while(start < end) {
        const int med = (start + end) / 2;
        
        if(name > m_images[med].name)
            start = med + 1;
        else
            end = med;
    }
    
    return start;
}

QSize ld::TileSheet::tileSize() const {
    return m_tileSize;
}
