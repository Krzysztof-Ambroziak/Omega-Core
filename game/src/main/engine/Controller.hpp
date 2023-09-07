/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Timer.hpp"

class MapModel;
class MapService;
class TileRenderer;
class TileRenderingService;
class Window;

class Controller {
public:
    Controller(Window* widget, MapModel* mapModel);
    
    void init();
    
    void start();

private:
    Timer m_timer;
    
    MapService* const m_mapService;
    
    TileRenderer* const m_renderer;
    
    TileRenderingService* const m_tileRenderingService;
    
    Window* const m_window;
};

#endif  // CONTROLLER_HPP
