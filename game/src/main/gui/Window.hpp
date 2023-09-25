/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Observable.hpp"

#include <QWidget>

class IRenderer;
class QMouseEvent;

class Window : public QWidget, public dp::Observable<QMouseEvent*> {
public:
    explicit Window(QWidget* const parent = nullptr);
    
    void setRenderer(IRenderer* const renderer);

protected:
    void paintEvent(QPaintEvent* const event) override;
    
    void mousePressEvent(QMouseEvent* const event) override;
    
    void mouseReleaseEvent(QMouseEvent* const event) override;

private:
    IRenderer* m_renderer;
};

#endif  // WINDOW_HPP
