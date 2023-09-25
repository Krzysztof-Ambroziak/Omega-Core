/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <QApplication>
#include <QScreen>
#include "../engine/Controller.hpp"
#include "../models/AssetsModel.hpp"
#include "../models/InputEventModel.hpp"
#include "../models/MapModel.hpp"
#include "../models/ScreenModel.hpp"
#include "../gui/Window.hpp"

class Game {
public:
    Game();
    
    void start();

private:
    Window m_window;
    AssetsModel m_assetsModel;
    InputEventModel m_inputEventModel;
    MapModel m_mapModel;
    ScreenModel m_screenModel;
    Controller m_controller;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    Game game;
    game.start();
    
    return QApplication::exec();
}

Game::Game() : m_controller(&m_window, &m_inputEventModel, &m_assetsModel, &m_mapModel, &m_screenModel) {
    m_screenModel.setScreen(m_window.screen());
}

void Game::start() {
    m_controller.init();
    m_controller.start();
}
