/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_TILESHEET_HPP
#define LD_TILESHEET_HPP

#include <QImage>
#include <QVector>

#include "Commons.hpp"

namespace ld {
class TileSheet {
private:
    struct NamedImage {
        QImage image;
        QString name;
    };

public:
    static const TileSheet NULL_TILESHEET;

private:
    static constexpr auto L_COMPARATOR = [](const auto& a, const auto& b) -> bool { return a.name < b.name; };

public:
    TileSheet(const QString& tileNamespace,
              TileType tileType,
              const QSize& m_tileSize);
    
    void addImage(const QImage& image,
                  const QString& name,
                  bool* repleace = nullptr);
    
    QString sheetNamespace() const;
    
    QStringList keys() const;
    
    QImage image(const QString& name) const;
    
    TileType tileType() const;
    
    QSize tileSize() const;

private:
    const QString c_tileNamespace;
    
    const TileType c_tileType;
    
    const QSize c_tileSize;
    
    QVector<NamedImage> m_images;
};

inline const TileSheet TileSheet::NULL_TILESHEET(QString(),
                                                 TileType::TILE_TYPE_UNKNOWN,
                                                 QSize());
}  // namespace ld

#endif  // LD_TILESHEET_HPP
