/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef TIMER_HPP
#define TIMER_HPP

#include <QTimer>

class QWidget;

class Timer : public QObject {
public:
    Timer(QWidget* widget, int ups, QObject* parent = nullptr);
    
    void start();
    
    void stop();

private slots:
    void tick();

private:
    QWidget* const m_widget;
    
    const int c_dt;
    
    QTimer timer;
};

#endif  // TIMER_HPP
