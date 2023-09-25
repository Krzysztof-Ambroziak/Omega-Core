/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "Window.hpp"
#include "../renderers/NullRenderer.hpp"

#include <QPainter>

Window::Window(QWidget* parent) :
        QWidget{parent},
        m_renderer(&NullRenderer::instance()) {}

void Window::setRenderer(IRenderer* const renderer) {
    m_renderer = renderer;
}

void Window::paintEvent(QPaintEvent* const event) {
    static QPainter painter;
    painter.begin(this);
    m_renderer->render(painter);
    painter.end();
}

void Window::mousePressEvent(QMouseEvent* event) {
    notifyObservers(event);
}

void Window::mouseReleaseEvent(QMouseEvent* event) {
    notifyObservers(event);
}
