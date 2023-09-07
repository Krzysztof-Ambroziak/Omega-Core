/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef MAPMODEL_HPP
#define MAPMODEL_HPP

#include "api/IMapModel.hpp"

#include <QPoint>
#include <QSize>
#include <QVector>

class MapModel : public IMapModel {
public:
    const QPixmap& tile(const ld::Position& position) const override;
    
    void addTile(const ld::Position& position, const QPixmap& image);
    
    void setMapSize(const ld::MapSize& mapSize);
    ld::MapSize mapSize() const;

public:
    QPoint originPoint() const override { return {0, 0}; };
    QSize tileHalfSize() const override { return {0, 0}; };

private:
    int index(const ld::Position& position) const;

private:
    ld::MapSize m_mapSize;
    
    QVector<QPixmap> m_tiles;
};

#endif  // MAPMODEL_HPP
