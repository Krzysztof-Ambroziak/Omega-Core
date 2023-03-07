/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <QApplication>
#include "loader/Loader.hpp"
#include "loader/Map.hpp"
#include "loader/TileSheet.hpp"
#include "../models/MapModel.hpp"
#include "../gui/Window.hpp"
#include "../renderers/IsometricTileRenderer.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    const ld::TileSheet& tileSheet = ld::Loader::loadTiles(":/tiles/xml/background-tile.xml",
                                                           ":/tiles/images/background-tile.png");
    const ld::Map& map = ld::Loader::loadMap(":/maps/start-map.xml");
    
    Window window;
    MapModel* const mapModel = new MapModel;
    mapModel->setMapSize(map.size());
    
    for(int row = 0; row < mapModel->mapSize().rows; row++)
        for(int column = 0; column < mapModel->mapSize().columns; column++) {
            const ld::Position position{column, row};
            const QString& imageName = map.tile(position);
            mapModel->addTile(position, QPixmap::fromImage(tileSheet.image(imageName)));
        }
    
    IsometricTileRenderer* renderer = new IsometricTileRenderer;
    renderer->setMapModel(mapModel);
    renderer->setTileSize(tileSheet.tileSize());
    renderer->setTilePositions();
    
    window.setRenderer(renderer);
    window.show();
    
    return QApplication::exec();
}
