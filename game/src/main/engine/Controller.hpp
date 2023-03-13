/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Timer.hpp"

class MapModel;
class MapService;
class IsometricTileRenderer;
class Window;

class Controller {
public:
    Controller(Window* widget, MapModel* mapModel);
    
    void init();
    
    void start();

private:
    Timer m_timer;
    
    MapService* const m_mapService;
    
    IsometricTileRenderer* const m_renderer;
    
    Window* const m_window;
};

#endif  // CONTROLLER_HPP
