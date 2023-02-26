/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef IRENDERER_HPP
#define IRENDERER_HPP

#include "../../OCGlobal.hpp"

class QPainter;

class IRenderer {
public:
    virtual void render(QPainter& painter) = 0;
    
    virtual oc::RendererType type() const = 0;
};

#endif  // IRENDERER_HPP
