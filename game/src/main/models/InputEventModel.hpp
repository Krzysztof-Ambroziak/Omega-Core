/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef INPUTEVENTMODEL_HPP
#define INPUTEVENTMODEL_HPP

#include <QEvent>
#include <QPointF>
#include <QVector>

class QMouseEvent;

class InputEventModel {
    struct Event {
        QEvent::Type type;
        Qt::KeyboardModifiers modifiers;
        QPointF point;
    };

public:
    void addEvent(QMouseEvent* event, const QPointF& point);

private:
    QVector<Event> m_events;
};

#endif // INPUTEVENTMODEL_HPP
