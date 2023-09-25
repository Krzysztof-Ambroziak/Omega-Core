/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "Timer.hpp"
#include "../services/api/IUpdateService.hpp"

#include <QDateTime>
#include <QWidget>

Timer::Timer(QWidget* widget, IUpdateService* updateService, int ups, QObject* parent) :
        QObject(parent),
        m_widget(widget),
        m_updateService(updateService),
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
        m_updateService->update(c_dt);
        delta -= c_dt;
    }
    
    m_widget->repaint();
}
