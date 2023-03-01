/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef MAPMODEL_HPP
#define MAPMODEL_HPP

#include "api/IMapModel.hpp"

#include <QVector>

class MapModel : public IMapModel {
public:
    const QPixmap* tile(const ld::Position& position) const override;
    
    void addTile(const ld::Position& position, const QPixmap& image);
    
    void setMapSize(const ld::MapSize& mapSize);

private:
    int index(const ld::Position& position) const;

private:
    QVector<const QPixmap*> m_tiles;
};

#endif  // MAPMODEL_HPP
