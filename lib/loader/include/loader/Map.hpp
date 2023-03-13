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
    Map(const QString& name, const MapSize& size, const QStringList& tileNamespaces);
    
    QString name() const;
    
    MapSize size() const;
    
    QStringList tileNamespaces() const;
    
    QString tile(const Position& position) const;
    
    void addTile(const Position& position, const QString& tileName, bool* ok = nullptr);

private:
    int pos2ind(const Position& position) const;

private:
    const QString m_name;
    
    const MapSize m_size;
    
    const QStringList m_namespaces;
    
    QVector<QString> m_tiles;
};

inline const Map Map::NULL_MAP(QString(), {0, 0}, QStringList());
}  // namespace ld

#endif  // LD_MAP_HPP
