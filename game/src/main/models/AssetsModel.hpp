/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef ASSETSMODEL_HPP
#define ASSETSMODEL_HPP

#include "Commons.hpp"

class AssetsModel {
    static constexpr auto L_TILE_COMPARATOR = [](const auto& a,
                                                 const auto& b) -> bool { return a.name < b.name; };

public:
    void addTile(const ld::Tile& tile);
    const QPixmap& tile(const QString& name) const;

private:
    QVector<ld::Tile> m_tiles;
};

#endif  // ASSETSMODEL_HPP
