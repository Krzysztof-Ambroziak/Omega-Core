/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <QApplication>
#include "../engine/Controller.hpp"
#include "../models/MapModel.hpp"
#include "../gui/Window.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    Window window;
    MapModel mapModel;
    Controller controller(&window, &mapModel);
    
    controller.init();
    controller.start();
    
    return QApplication::exec();
}
