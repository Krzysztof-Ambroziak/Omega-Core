/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef TILERENDERER_HPP
#define TILERENDERER_HPP

#include "../OCGlobal.hpp"
#include "api/IRenderer.hpp"

#include <QVector>

class IMapModel;
class IScreenModel;

namespace ld {
struct MapSize;
}

class TileRenderer : public IRenderer {
public:
    TileRenderer(const IMapModel* mapModel,
                 const IScreenModel* screenModel);
    
    void setTilePositions(const QVector<oc::TilePosition>& tilePositions);

public:
    void render(QPainter& painter) override;

private:
    const IMapModel* const m_mapModel;
    
    const IScreenModel* const m_screenModel;
    
    QVector<oc::TilePosition> m_positions;
};

#endif  // TILERENDERER_HPP
