/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <algorithm>  /* std::lower_bound */

#include "../../include/loader/TileSheet.hpp"
#include "utilities/PrivateHelpers.hpp"

QVector<ld::TileSheet::NamedImage>::const_iterator ld::TileSheet::nextValue(QVector<NamedImage>::const_iterator begin,
                                                                            QVector<NamedImage>::const_iterator end) {
    if(begin < end) {
        const QString& name = begin->name;
        while(begin < end && begin->name == name)
            begin++;
    }
    
    return begin;
}

QVector<ld::TileSheet::NamedImage> ld::TileSheet::same(QVector<NamedImage>::const_iterator begin,
                                                       QVector<NamedImage>::const_iterator end) {
    return QVector<NamedImage>(begin, nextValue(begin, end));
}

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

ld::TileSheet& ld::TileSheet::merge(const TileSheet& tileSheet, MergeMethod method) {
    const auto& newTiles = tileSheet.m_images;
    
    if(newTiles.isEmpty())
        return *this;
    if(m_images.isEmpty()) {
        m_images.append(newTiles);
        return *this;
    }
    
    const QVector<NamedImage> ownTiles(m_images);
    m_images.clear();
    m_images.reserve(ownTiles.size() + newTiles.size());
    auto itOwnB = ownTiles.cbegin();
    auto itNewB = newTiles.cbegin();
    const auto itOwnE = ownTiles.cend();
    const auto itNewE = newTiles.cend();
    
    while(true) {
        const QString& ownTileName = itOwnB->name;
        const QString& newTileName = itNewB->name;
        
        if(itOwnB->name < itNewB->name)
            m_images.append(*itOwnB++);
        else if(itNewB->name < itOwnB->name)
            m_images.append(*itNewB++);
        else
            switch(method) {
            case ADD:
                m_images.append(same(itOwnB, itOwnE));
                itOwnB = nextValue(itOwnB, itOwnE);
                break;
            case IGNORE:
                m_images.append(same(itOwnB, itOwnE));
                itOwnB = nextValue(itOwnB, itOwnE);
                itNewB = nextValue(itNewB, itNewE);
                break;
            case OVERRIDE:
                m_images.append(same(itNewB, itNewE));
                itOwnB = nextValue(itOwnB, itOwnE);
                itNewB = nextValue(itNewB, itNewE);
                break;
            }
        
        if(itOwnB == itOwnE) {
            m_images.append({itNewB, itNewE});
            break;
        }
        if(itNewB == itNewE) {
            m_images.append({itOwnB, itOwnE});
            break;
        }
    }
    
    return *this;
}
