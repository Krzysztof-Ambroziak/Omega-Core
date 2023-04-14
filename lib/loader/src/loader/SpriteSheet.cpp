/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <algorithm>  /* std::lower_bound */

#include "../../include/loader/SpriteSheet.hpp"
#include "utilities/PrivateHelpers.hpp"

const ld::Sprite& ld::SpriteSheet::sprite(const QString& name) const {
    static NamedSprite emptyNamedSprite;
    emptyNamedSprite.name = name;
    const auto& it = std::lower_bound<>(m_sprites.cbegin(),
                                        m_sprites.cend(),
                                        emptyNamedSprite,
                                        L_COMPARATOR);
    
    if(it < m_sprites.cend() && name == it->name)
        return it->sprite;
    
    return emptyNamedSprite.sprite;
}

void ld::SpriteSheet::addSprite(const Sprite& sprite, const QString& name, bool* repleace) {
    const NamedSprite namedSprite{name, sprite};
    const auto& it = std::lower_bound<>(m_sprites.begin(),
                                        m_sprites.end(),
                                        namedSprite,
                                        L_COMPARATOR);
    
    if(it < m_sprites.end() && name == it->name) {
        it->sprite = sprite;
        ld::setPVar<>(true, repleace);
    }
    else {
        m_sprites.insert(it, namedSprite);
        ld::setPVar<>(false, repleace);
    }
}

QStringList ld::SpriteSheet::keys() const {
    QStringList keys;
    
    for(const NamedSprite& namedSprite : m_sprites)
        keys += namedSprite.name;
    
    return keys;
}
