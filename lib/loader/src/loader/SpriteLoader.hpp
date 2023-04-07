/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_SPRITELOADER_HPP
#define LD_SPRITELOADER_HPP

#include "../../include/loader/SpriteSheet.hpp"

#include <QXmlStreamReader>

namespace ld {
class Sprite;

class SpriteLoader {
private:
    struct SpriteDefinition {
        QString name;
        int images = 0;
        QRect position;
        QPoint pivot;
    };

public:
    SpriteLoader(const QString& defFilename, const QImage& image);
    
    SpriteSheet loadSprites();

private:
    SpriteSheet readSprites();
    
    SpriteDefinition readSprite();
    
    QRect readSpritePosition();
    
    QPoint readPivotPoint();
    
    QVector<QPixmap> copySubimage(const QRect& bound, int count) const;

private:
    QXmlStreamReader m_reader;
    
    QImage m_image;

private:
    inline static const QString ROOT = "sprites";
    inline static const QString SPRITE = "sprite";
    inline static const QString NAME = "name";
    inline static const QString IMAGES = "images";
    inline static const QString POSITION = "position";
    inline static const QString PIVOT = "pivot";
    inline static const QString POS_X = "x";
    inline static const QString POS_Y = "y";
    inline static const QString POS_WIDTH = "width";
    inline static const QString POS_HEIGHT = "height";
};
}  // namespace ld

#endif  // LD_SPRITELOADER_HPP
