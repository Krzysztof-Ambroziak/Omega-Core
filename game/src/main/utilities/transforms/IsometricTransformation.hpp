/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef ISOMETRICTRANSFORMATION_HPP
#define ISOMETRICTRANSFORMATION_HPP

#include "TransformationAdapter.hpp"
#include "../../OCGlobal.hpp"

class IsometricTransformation : public TransformationAdapter {
public:
    static IsometricTransformation& instance(oc::Rotation rotation);

public:
    IsometricTransformation(const IsometricTransformation& o) = delete;
    
    void setTileSize(const QSize& size);

private:
    IsometricTransformation();
    
    IsometricTransformation(int m11, int m12, int m21, int m22);
};

#endif  // ISOMETRICTRANSFORMATION_HPP
