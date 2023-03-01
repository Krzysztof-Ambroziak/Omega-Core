/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef IMAPMODEL_HPP
#define IMAPMODEL_HPP

#include "Commons.hpp"

class QPixmap;

class IMapModel {
public:
    virtual const QPixmap* tile(const ld::Position& position) const = 0;
    
    ld::MapSize mapSize() const;

protected:
    ld::MapSize m_mapSize;
};

inline ld::MapSize IMapModel::mapSize() const {
    return m_mapSize;
}

#endif  // IMAPMODEL_HPP
