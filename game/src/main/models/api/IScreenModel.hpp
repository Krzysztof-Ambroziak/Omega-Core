/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef ISCREENMODEL_HPP
#define ISCREENMODEL_HPP

#include <QtGlobal>

class QPoint;
class QSize;

class IScreenModel {
public:
    virtual QSize screenSize() const = 0;
    
    virtual QPoint centerPoint() const = 0;
    
    virtual qreal refreshRate() const = 0;
};

#endif  // ISCREENMODEL_HPP
