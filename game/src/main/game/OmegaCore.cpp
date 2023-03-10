/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <QApplication>
#include "../models/MapModel.hpp"
#include "../gui/Window.hpp"
#include "../renderers/IsometricTileRenderer.hpp"
#include "../services/MapService.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    MapModel* const mapModel = new MapModel;
    MapService mapService(mapModel);
    
    mapService.loadTileSheet(":/tiles/xml/background-tile.xml",
                             ":/tiles/images/background-tile.png");
    mapService.loadMap(":/maps/start-map.xml");
    
    mapService.changeMap("start");
    
    Window window;
    
    IsometricTileRenderer* renderer = new IsometricTileRenderer;
    renderer->setMapModel(mapModel);
    renderer->setTileSize({64, 32});
    renderer->setTilePositions();
    
    window.setRenderer(renderer);
    window.show();
    
    return QApplication::exec();
}
