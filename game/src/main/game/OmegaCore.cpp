/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <QApplication>
#include "loader/Loader.hpp"
#include "loader/TileSheet.hpp"
#include <QWidget>
#include <QPainter>

class Window : public QWidget {
public:
    Window(const QImage& rock, const QImage& water, const QImage& sand, const QImage& grass) :
        m_rock(rock),
        m_water(water),
        m_sand(sand),
        m_grass(grass) {}

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    const QImage m_rock;
    const QImage m_water;
    const QImage m_sand;
    const QImage m_grass;
};

void Window::paintEvent(QPaintEvent* event) {
    QPainter painter;
    painter.begin(this);
    painter.drawImage(0, 0, m_rock);
    painter.drawImage(m_water.width() + 10, 0, m_water);
    painter.drawImage(0, m_sand.height() + 10, m_sand);
    painter.drawImage(m_grass.width() + 10, m_grass.height() + 10, m_grass);
    painter.end();
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    const ld::TileSheet& temp = ld::Loader::loadTiles(":/tiles/xml/background-tile.xml",
                                                      ":/tiles/images/background-tile.png");
    const QImage& rock = temp.image("rock");
    const QImage& water = temp.image("water");
    const QImage& sand = temp.image("sand");
    const QImage& grass = temp.image("grass");
    Window window(rock, water, sand, grass);
    window.show();
    
    return QApplication::exec();
}
