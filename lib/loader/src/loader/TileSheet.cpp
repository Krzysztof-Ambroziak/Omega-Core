/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "../../include/loader/TileSheet.hpp"

void setPBool(bool var, bool* pointer) {
    if(pointer != nullptr)
        *pointer = var;
}

ld::TileSheet::TileSheet(const QString& tileNamespace, ld::TileType tileType) :
        m_sheetNamespace(tileNamespace),
        m_tileType(tileType) {}

void ld::TileSheet::addImage(const QImage& image, const QString& name, bool* repleace) {
    const int end = m_images.size();
    const int index = binarySearchIndex(name);
    
    if(index < end && name == m_images[index].name) {
        setPBool(true, repleace);
        m_images[index] = {image, name};
    }
    else {
        setPBool(false, repleace);
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
