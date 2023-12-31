/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_SPRITE_HPP
#define LD_SPRITE_HPP

#include <QPixmap>

namespace ld {
class Sprite {
public:
    QPoint pivot() const;
    void setPivot(QPoint pivot);
    
    const QPixmap& image(int index) const;
    void addImage(const QPixmap& pixmap);
    void addImages(const QVector<QPixmap>& pixmaps);
    
    int size() const;

private:
    QPoint m_pivot;
    
    QVector<QPixmap> m_images;
};
}  // namespace ld

#endif  // LD_SPRITE_HPP
