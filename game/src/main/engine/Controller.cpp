/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "Controller.hpp"
#include "../models/InputEventModel.hpp"
#include "../models/MapModel.hpp"
#include "../models/ScreenModel.hpp"
#include "../renderers/TileRenderer.hpp"
#include "../services/MapService.hpp"
#include "../services/TileRenderingService.hpp"
#include "../services/UpdateService.hpp"
#include "../utilities/transforms/IsometricTransformation.hpp"
#include "../gui/Window.hpp"

Controller::Controller(Window* const window,
                       InputEventModel* const inputEventModel,
                       AssetsModel* const assetsModel,
                       MapModel* const mapModel,
                       ScreenModel* const screenModel) :
        m_window(window),
        m_inputEventModel(inputEventModel),
        m_updateService(new UpdateService(inputEventModel)),
        m_timer(m_window, m_updateService, 10),
        m_mapService(new MapService(assetsModel, mapModel)),
        m_renderer(new TileRenderer(mapModel, screenModel)),
    m_tileRenderingService(new TileRenderingService(m_renderer)) {
    m_window->addObserver(this);
}

void Controller::init() {
    m_mapService->changeMap("start");
    m_tileRenderingService->changeTileQueue(m_mapService->mapSize(), {64, 32});
    m_window->setRenderer(m_renderer);
}

void Controller::start() {
    m_window->show();
    m_timer.start();
}

void Controller::update(QMouseEvent* const& arg) {
    IsometricTransformation& transformation =
        IsometricTransformation::instance(oc::Rotation::ROTATION_0_DEG);
    transformation.setTileSize({64, 32});
    
    const auto& point = transformation.transform(arg->pos());
    m_inputEventModel->addEvent(arg, point);
}
