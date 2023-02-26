/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <QApplication>
#include "loader/Loader.hpp"
#include "loader/TileSheet.hpp"
#include "../gui/Window.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    const ld::TileSheet& temp = ld::Loader::loadTiles(":/tiles/xml/background-tile.xml",
                                                      ":/tiles/images/background-tile.png");
    Window window;
    window.show();
    
    return QApplication::exec();
}
