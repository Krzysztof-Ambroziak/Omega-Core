/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <algorithm>  /* std::lower_bound */

#include <QStringList>

#include "../../include/loader/MapSheet.hpp"

const ld::Map& ld::MapSheet::map(const QString& name) const {
    static NamedMap emptyNamedMap {name, ld::Map::NULL_MAP};
    const auto& it = std::lower_bound<>(m_maps.cbegin(),
                                        m_maps.cend(),
                                        emptyNamedMap,
                                        L_COMPARATOR);
    
    if(it < m_maps.cend() && name == it->name)
        return it->map;
    
    return emptyNamedMap.map;
}

void ld::MapSheet::addMap(const ld::Map& map, const QString& name) {
    const NamedMap namedMap{name, map};
    const auto& it = std::lower_bound<>(m_maps.begin(),
                                        m_maps.end(),
                                        namedMap,
                                        L_COMPARATOR);
    
    if(it < m_maps.end() && name == it->name)
        it->map = map;
    else
        m_maps.insert(it, namedMap);
}

QStringList ld::MapSheet::keys() const {
    QStringList keys;
    
    for(const NamedMap& map : m_maps)
        keys += map.name;
    
    return keys;
}
