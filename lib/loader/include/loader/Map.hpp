/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_MAP_HPP
#define LD_MAP_HPP

#include <QVector>

#include "Commons.hpp"

namespace ld {
class Map {
public:
    static const Map NULL_MAP;

public:
    Map() = default;
    Map(const MapSize& size);
    
    MapSize size() const;
    void setSize(const MapSize& size);
    
    QString tile(const Position& position) const;
    void addTile(const Position& position, const QString& tileName, bool* ok = nullptr);
    
    bool operator==(const Map& map) const;

private:
    int pos2ind(const Position& position) const;

private:
    MapSize m_size;
    
    QVector<QString> m_tiles;
};

inline const Map Map::NULL_MAP({0, 0});
}  // namespace ld

#endif  // LD_MAP_HPP
