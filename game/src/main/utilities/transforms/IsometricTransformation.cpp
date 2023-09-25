/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "IsometricTransformation.hpp"

IsometricTransformation& IsometricTransformation::instance(oc::Rotation rotation) {
    static IsometricTransformation transformation1(1, -1, 1, 1);
    static IsometricTransformation transformation2(-1, -1, -1, 1);
    static IsometricTransformation transformation3(-1, 1, -1, -1);
    static IsometricTransformation transformation4(1, 1, -1, 1);
    static IsometricTransformation transformationIdentity;
    
    switch(rotation) {
    case oc::ROTATION_0_DEG:
        return transformation1;
    case oc::ROTATION_90_DEG:
        return transformation2;
    case oc::ROTATION_180_DEG:
        return transformation3;
    case oc::ROTATION_270_DEG:
        return transformation4;
    default:
        return transformationIdentity;
    }
}

void IsometricTransformation::setTileSize(const QSize& size) {
    const auto w = size.width();
    const auto h = size.height();
    
    m_r11 = M_11/double(w);
    m_r12 = M_12/double(h);
    m_r21 = M_21/double(w);
    m_r22 = M_22/double(h);
}

IsometricTransformation::IsometricTransformation() : TransformationAdapter() {}

IsometricTransformation::IsometricTransformation(int m11, int m12, int m21, int m22) :
        TransformationAdapter(m11, m12, m21, m22) {}
