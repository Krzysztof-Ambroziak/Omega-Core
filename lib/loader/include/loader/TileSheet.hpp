/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_TILESHEET_HPP
#define LD_TILESHEET_HPP

#include <QPixmap>
#include <QVector>

#include "Commons.hpp"

namespace ld {
class TileSheet {
public:
    enum MergeMethod {
        OVERRIDE,
        IGNORE,
        ADD
    };

private:
    struct NamedImage {
        QString name;
        QPixmap image;
    };
    
    static constexpr auto L_COMPARATOR = [](const auto& a, const auto& b) -> bool { return a.name < b.name; };

public:
    static const TileSheet NULL_TILESHEET;

public:
    TileSheet();
    TileSheet(TileType tileType, const QSize& m_tileSize);
    
    TileType tileType() const;
    void setTileType(TileType tileType);
    
    QSize tileSize() const;
    void setTileSize(const QSize& tileSize);
    
    const QPixmap& image(const QString& name) const;
    void addImage(const QPixmap& image,
                  const QString& name,
                  bool* repleace = nullptr);
    
    QStringList keys() const;

private:
    TileType m_tileType;
    
    QSize m_tileSize;
    
    QVector<NamedImage> m_images;
};

inline const TileSheet TileSheet::NULL_TILESHEET(TileType::TILE_TYPE_UNKNOWN,
                                                 QSize());
}  // namespace ld

#endif  // LD_TILESHEET_HPP
