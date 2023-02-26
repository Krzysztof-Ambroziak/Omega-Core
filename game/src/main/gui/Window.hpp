/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QWidget>

class IRenderer;

class Window : public QWidget {
public:
    explicit Window(QWidget* parent = nullptr);
    
    void setRenderer(IRenderer* renderer);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    IRenderer* m_renderer;
};

#endif  // WINDOW_HPP
