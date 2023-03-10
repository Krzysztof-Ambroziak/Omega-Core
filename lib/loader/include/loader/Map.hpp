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
    Map(const MapSize& size, const QString& name);
    
    MapSize size() const;
    
    QString name() const;
    
    QString tile(const Position& position) const;
    
    void addTile(const Position& position, const QString& tileName, bool* ok = nullptr);

private:
    int indexFromPosition(const Position& position) const;

private:
    const MapSize m_size;
    
    const QString m_name;
    
    QVector<QString> m_tiles;
};

inline const Map Map::NULL_MAP({0, 0}, QString());
}  // namespace ld

#endif  // LD_MAP_HPP
