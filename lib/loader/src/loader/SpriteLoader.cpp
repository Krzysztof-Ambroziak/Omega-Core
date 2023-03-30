/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "SpriteLoader.hpp"
#include "../../include/loader/Sprite.hpp"

ld::SpriteLoader::SpriteLoader(const QString& def, const QImage& image) :
        m_reader(def),
        m_image(image) {}

QVector<ld::Sprite> ld::SpriteLoader::loadSprites() {
    if(!m_reader.readNextStartElement() || m_reader.name() != ROOT)
        return {};
    
    return readSprites();
}

QVector<ld::Sprite> ld::SpriteLoader::readSprites() {
    QVector<ld::Sprite> sprites;
    
    while(m_reader.readNextStartElement())
        if(m_reader.name() == SPRITE) {
            const SpriteDefinition& spriteDef = readSprite();
            
            if(spriteDef.name.isEmpty() || spriteDef.images < 1)
                continue;
            
            const QVector<QPixmap>& images = copySubimage(spriteDef.position, spriteDef.images);
            
            ld::Sprite sprite;
            sprite.setName(spriteDef.name);
            sprite.setPivot(spriteDef.pivot);
            sprite.addImages(images);
            
            sprites += sprite;
        }
    
    return sprites;
}

ld::SpriteLoader::SpriteDefinition ld::SpriteLoader::readSprite() {
    SpriteDefinition spriteDefinition {QString(), 0, {}};
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        
        if(name == NAME)
            spriteDefinition.name = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                                            .trimmed();
        if(name == IMAGES)
            spriteDefinition.images = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                                              .trimmed()
                                              .toInt();
        if(name == POSITION)
            spriteDefinition.position = readSpritePosition();
        if(name == PIVOT)
            spriteDefinition.pivot = readPivotPoint();
    }
    
    return spriteDefinition;
}

QRect ld::SpriteLoader::readSpritePosition() {
    int x = -1;
    int y = -1;
    int width = 0;
    int height = 0;
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        bool ok;
        const int value = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                                  .trimmed()
                                  .toInt(&ok);
        
        if(name == POS_X && ok)
            x = value;
        if(name == POS_Y && ok)
            y = value;
        if(name == POS_WIDTH && ok)
            width = value;
        if(name == POS_HEIGHT && ok)
            height = value;
    }
    
    return (x >= 0 && y >= 0 && width > 0 && height > 0) ? QRect(x, y, width, height) : QRect();
}

QPoint ld::SpriteLoader::readPivotPoint() {
    QPoint pivot;
    
    while(m_reader.readNextStartElement()) {
        const QStringRef& name = m_reader.name();
        int value = m_reader.readElementText(QXmlStreamReader::SkipChildElements)
                            .trimmed().toInt();
        
        if(name == POS_X)
            pivot.setX(value);
        if(name == POS_Y)
            pivot.setY(value);
    }
    
    return pivot;
}

QVector<QPixmap> ld::SpriteLoader::copySubimage(const QRect& bound, int count) const {
    QVector<QPixmap> images;
    const QRect& imageBound = m_image.rect();
    const int width = bound.width();
    const int height = bound.height();
    
    for(int i = 0; i < count; i++) {
        const QRect subBound(bound.x() + i * width, bound.y() + i * height, width, height);
        images += (imageBound.contains(subBound) ?
                       QPixmap::fromImage(m_image.copy(subBound)) :
                       QPixmap());
    }
    
    return images;
}
