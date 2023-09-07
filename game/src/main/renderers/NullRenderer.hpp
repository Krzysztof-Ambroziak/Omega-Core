/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef NULLRENDERER_HPP
#define NULLRENDERER_HPP

#include "api/IRenderer.hpp"

class NullRenderer : public IRenderer {
public:
    static NullRenderer& instance();

public:
    NullRenderer(const NullRenderer& renderer) = delete;
    
    void render(QPainter& /*painter*/) override {}

private:
    NullRenderer() = default;
};

inline NullRenderer& NullRenderer::instance() {
    static NullRenderer renderer;
    return renderer;
}

#endif  // NULLRENDERER_HPP
