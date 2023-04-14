/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "Controller.hpp"
#include "../models/MapModel.hpp"
#include "../renderers/IsometricTileRenderer.hpp"
#include "../services/MapService.hpp"
#include "../gui/Window.hpp"

Controller::Controller(Window* const window, MapModel* const mapModel) :
        m_timer(window, 10),
        m_mapService(new MapService(mapModel)),
        m_renderer(new IsometricTileRenderer),
        m_window(window) {
    m_renderer->setMapModel(mapModel);
}

void Controller::init() {
    m_mapService->loadTileSheet(":/tiles/xml/background-tile.xml",
                                ":/tiles/images/background-tile.png");
    m_mapService->loadSpriteSheet(":/sprites/xml/sprites.xml",
                                  ":/sprites/images/sprites.png");
    m_mapService->loadMap(":/maps/start-map.xml");
    
    m_mapService->changeMap("start");
    m_renderer->setTileSize({64, 32});
    m_renderer->setTilePositions();
    m_window->setRenderer(m_renderer);
}

void Controller::start() {
    m_window->show();
    m_timer.start();
}
