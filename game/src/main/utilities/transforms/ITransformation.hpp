/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef ITRANSFORMATION_HPP
#define ITRANSFORMATION_HPP

class QPoint;
class QPointF;

class ITransformation {
public:
    virtual QPointF transform(const QPoint& point) const = 0;
};

#endif  // ITRANSFORMATION_HPP
