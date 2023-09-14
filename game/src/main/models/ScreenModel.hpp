/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef SCREENMODEL_HPP
#define SCREENMODEL_HPP

#include "api/IScreenModel.hpp"

class QScreen;

class ScreenModel : public IScreenModel {
public:
    void setScreen(const QScreen* screen);
    
    QSize screenSize() const override;
    
    QPoint centerPoint() const override;
    
    qreal refreshRate() const override;

private:
    const QScreen* m_screen;
};

#endif  // SCREENMODEL_HPP
