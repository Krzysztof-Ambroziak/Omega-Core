/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_SPRITESHEET_HPP
#define LD_SPRITESHEET_HPP

#include "Sprite.hpp"

namespace ld {
class SpriteSheet {
private:
    struct NamedSprite {
        QString name;
        Sprite sprite;
    };

private:
    static constexpr auto L_COMPARATOR = [](const auto& a, const auto& b) -> bool { return a.name < b.name; };

public:
    const Sprite& sprite(const QString& name) const;
    void addSprite(const Sprite& sprite,
                   const QString& name,
                   bool* repleace = nullptr);
    
    QStringList keys() const;

private:
    QVector<NamedSprite> m_sprites;
};
}  // namespace ld

#endif  // LD_SPRITESHEET_HPP
