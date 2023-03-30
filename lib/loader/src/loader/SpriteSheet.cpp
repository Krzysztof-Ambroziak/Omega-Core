/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include <algorithm>  /* std::lower_bound */

#include "../../include/loader/SpriteSheet.hpp"
#include "utilities/PrivateHelpers.hpp"

void ld::SpriteSheet::addSprite(const Sprite& sprite,
                                const QString& name,
                                bool* repleace) {
    const NamedSprite newNamedSprite {name, sprite};
    const auto& it = std::lower_bound<>(m_sprites.begin(),
                                        m_sprites.end(),
                                        newNamedSprite,
                                        L_COMPARATOR);
    
    if(it < m_sprites.end() && name == it->name) {
        it->sprite = newNamedSprite.sprite;
        ld::setPVar<>(true, repleace);
    }
    else {
        m_sprites.insert(it, newNamedSprite);
        ld::setPVar<>(false, repleace);
    }
}
