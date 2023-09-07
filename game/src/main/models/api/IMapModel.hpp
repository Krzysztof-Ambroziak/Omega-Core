/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef IMAPMODEL_HPP
#define IMAPMODEL_HPP

#include "Commons.hpp"
#include <QVector>

class QPixmap;
class QPoint;
class QSize;

class IMapModel {
public:
    virtual const QPixmap& tile(const ld::Position& position) const = 0;
    
    virtual QPoint originPoint() const = 0;
    
    virtual QSize tileHalfSize() const  = 0;
};

#endif  // IMAPMODEL_HPP
