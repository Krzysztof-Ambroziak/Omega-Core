/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "ScreenModel.hpp"

#include <QScreen>

void ScreenModel::setScreen(const QScreen* const screen) {
    m_screen = screen;
}

QSize ScreenModel::screenSize() const {
    return m_screen->availableSize();
}

QPoint ScreenModel::centerPoint() const {
    static QSize size(0, 0);
    static QPoint cp(0, 0);
    
    if(const auto& s = m_screen->availableSize() ; size != s) {
        size = s;
        cp.setX(size.width() / 2);
        cp.setY(size.height() / 2);
    }
    
    return cp;
}

qreal ScreenModel::refreshRate() const {
    return m_screen->refreshRate();
}
