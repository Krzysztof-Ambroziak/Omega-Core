/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef TILERENDERINGSERVICE_HPP
#define TILERENDERINGSERVICE_HPP

#include "../OCGlobal.hpp"

#include <QVector>

class QSize;
class TileRenderer;

class TileRenderingService {
public:
    TileRenderingService(TileRenderer* m_tileRenderer);
    
    void changeTileQueue(const ld::MapSize& mapSize, const QSize& tileSize);
    
    void rotate(oc::DirectionOfRotation direction);

private:
    TileRenderer* const m_tileRenderer;
    
    ld::MapSize m_mapSize;
    
    QVector<oc::TilePosition> m_positions;
};

#endif  // TILERENDERINGSERVICE_HPP
