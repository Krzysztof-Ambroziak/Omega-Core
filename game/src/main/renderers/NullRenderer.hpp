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
    
    oc::RendererType type() const override;

private:
    NullRenderer() = default;
};

inline NullRenderer& NullRenderer::instance() {
    static NullRenderer renderer;
    return renderer;
}

oc::RendererType NullRenderer::type() const {
    return oc::NULL_RENDERER;
}

#endif  // NULLRENDERER_HPP
