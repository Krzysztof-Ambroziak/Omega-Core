/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef MAPSERVICE_HPP
#define MAPSERVICE_HPP

#include <QVector>

namespace ld {
class Map;
class TileSheet;
}  // namespace ld

namespace std {
template<class T>
class shared_ptr;
}  // namespace std

class MapModel;
class QPixmap;

class MapService {
public:
    MapService(MapModel* model);
    
    void loadTileSheet(const QString& definitionFilename,
                       const QString& imageFileName);
    
    void loadMap(const QString& definitionFilename);
    
    void changeMap(const QString& mapName);

private:
    std::shared_ptr<ld::Map> findMap(const QString& mapName) const;
    
    QPixmap findTile(const QString& tileName,
                     const QStringList& tileNamespaces) const;

private:
    QVector<std::shared_ptr<ld::TileSheet>> m_tileSheets;
    
    QVector<std::shared_ptr<ld::Map>> m_maps;
    
    MapModel* const m_mapModel;
};

#endif  // MAPSERVICE_HPP
