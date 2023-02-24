/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_MAP_HPP
#define LD_MAP_HPP

#include <QStringList>

#include "Commons.hpp"

namespace ld {
class Map {
public:
    static const Map NULL_MAP;

public:
    Map(const MapSize& size);
    
    MapSize size() const;
    
    void addTileNamespace(const QString& tileNamespace);
    
    void addTileNamespaces(const QStringList& tileNamespace);
    
    QStringList tileNamespaces() const;
    
    QString tile(const Position& position) const;
    
    void addTile(const Position& position, const QString& tileName, bool* ok = nullptr);

private:
    int indexFromPosition(const Position& position) const;

private:
    const MapSize m_size;
    
    QStringList m_tileNamespaces;
    
    QVector<QString> m_tiles;
};

inline const Map Map::NULL_MAP({0, 0});
}  // namespace ld

#endif  // LD_MAP_HPP
