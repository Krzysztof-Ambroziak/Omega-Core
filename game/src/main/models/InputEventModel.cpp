/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "InputEventModel.hpp"

#include <QDebug>
#include <QMouseEvent>

void InputEventModel::addEvent(QMouseEvent* const event, const QPointF& point) {
    m_events += { event->type(), event->modifiers(), point };
    qDebug() << point;
}
