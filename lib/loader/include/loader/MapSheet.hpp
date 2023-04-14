/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_MAPSHEET_HPP
#define LD_MAPSHEET_HPP

#include <QVector>

#include "loader/Map.hpp"

namespace ld {
class MapSheet {
private:
    struct NamedMap {
        QString name;
        ld::Map map;
    };
    
    static constexpr auto L_COMPARATOR = [](const auto& a, const auto& b) -> bool { return a.name < b.name; };

public:
    const ld::Map& map(const QString& name) const;
    void addMap(const ld::Map& map, const QString& name);
    
    QStringList keys() const;

private:
    QVector<NamedMap> m_maps;
};
}  // namespace ld

#endif  // LD_MAPSHEET_HPP
