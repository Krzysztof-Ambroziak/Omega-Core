/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "Window.hpp"
#include "../renderers/NullRenderer.hpp"

#include <QPainter>

Window::Window(QWidget* parent) :
        QWidget{parent},
        m_renderer(&NullRenderer::instance()) {}

void Window::setRenderer(IRenderer* renderer) {
    m_renderer = renderer;
}

void Window::paintEvent(QPaintEvent* event) {
    static QPainter painter;
    painter.begin(this);
    m_renderer->render(painter);
    painter.end();
}
