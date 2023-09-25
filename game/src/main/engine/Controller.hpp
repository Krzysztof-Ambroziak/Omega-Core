/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Timer.hpp"

#include "Observer.hpp"

#include <QMouseEvent>

class AssetsModel;
class InputEventModel;
class MapModel;
class MapService;
class ScreenModel;
class TileRenderer;
class TileRenderingService;
class UpdateService;
class Window;

class Controller : public dp::Observer<QMouseEvent*> {
    struct Event {
        QEvent::Type type;
        Qt::KeyboardModifiers modifiers;
        Qt::MouseButtons buttons;
        QPoint point;
    };

public:
    Controller(Window* widget,
               InputEventModel* inputEventModel,
               AssetsModel* assetsModel,
               MapModel* mapModel,
               ScreenModel* screenModel);
    
    void init();
    
    void start();

public:
    void update(QMouseEvent* const& arg) override;

private:
    Window* const m_window;
    
    InputEventModel* const m_inputEventModel;
    
    UpdateService* const m_updateService;
    
    Timer m_timer;
    
    MapService* const m_mapService;
    
    TileRenderer* const m_renderer;
    
    TileRenderingService* const m_tileRenderingService;
};

#endif  // CONTROLLER_HPP
