/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Timer.hpp"

class AssetsModel;
class MapModel;
class MapService;
class ScreenModel;
class TileRenderer;
class TileRenderingService;
class Window;

class Controller {
public:
    Controller(Window* widget, AssetsModel* assetsModel, MapModel* mapModel, ScreenModel* screenModel);
    
    void init();
    
    void start();

private:
    Window* const m_window;
    
    Timer m_timer;
    
    MapService* const m_mapService;
    
    TileRenderer* const m_renderer;
    
    TileRenderingService* const m_tileRenderingService;
};

#endif  // CONTROLLER_HPP
