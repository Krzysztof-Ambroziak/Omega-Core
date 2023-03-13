/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "Timer.hpp"

#include <QDateTime>
#include <QWidget>

Timer::Timer(QWidget* widget, int ups, QObject* parent) :
        QObject(parent),
        m_widget(widget),
        c_dt(1000000 / ups) {
    QObject::connect(&timer, &QTimer::timeout, this, &Timer::tick);
}

void Timer::start() {
    timer.start();
}

void Timer::stop() {
    if(timer.isActive())
        timer.stop();
}

void Timer::tick() {
    static int delta = 0;
    static auto prev = QDateTime::currentMSecsSinceEpoch();
    static auto curr = prev;
    static int i = 0;
    
    curr = QDateTime::currentMSecsSinceEpoch();
    delta += (curr - prev) * 1000;
    prev = curr;
    
    while(delta >= c_dt) {
        // update state;
        delta -= c_dt;
    }
    
    m_widget->repaint();
}
