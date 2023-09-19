/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "Controller.hpp"
#include "../models/MapModel.hpp"
#include "../models/ScreenModel.hpp"
#include "../renderers/TileRenderer.hpp"
#include "../services/MapService.hpp"
#include "../services/TileRenderingService.hpp"
#include "../gui/Window.hpp"

Controller::Controller(Window* const window,
                       AssetsModel* const assetsModel,
                       MapModel* const mapModel,
                       ScreenModel* const screenModel) :
        m_window(window),
        m_timer(m_window, 10),
        m_mapService(new MapService(assetsModel, mapModel)),
        m_renderer(new TileRenderer(mapModel, screenModel)),
        m_tileRenderingService(new TileRenderingService(m_renderer)) {
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
