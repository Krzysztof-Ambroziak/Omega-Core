/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef MAPSERVICE_HPP
#define MAPSERVICE_HPP

#include <QVector>

#include <memory>

#include "../models/MapModel.hpp"

namespace ld {
class Map;
}

class MapService {
private:
    struct PTile {
        QString name;
        QPixmap* image;
    };

public:
    MapService(MapModel* model);

    void loadTileSheet(const QString& definitionFilename,
                       const QString& imageFileName);

    void loadMap(const QString& definitionFilename);

    void changeMap(const QString& mapName);

    ~MapService();

private:
    QVector<PTile> m_tileSheets;

    QVector<std::shared_ptr<ld::Map>> m_maps;

    MapModel* const m_mapModel;
};

#endif  // MAPSERVICE_HPP
