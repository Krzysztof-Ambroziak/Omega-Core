/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#include "TransformationAdapter.hpp"

#include <QPointF>

QPointF TransformationAdapter::transform(const QPoint& point) const {
    const auto x = point.x();
    const auto y = point.y();
    
    return QPointF(m_r11*x+m_r12*y, m_r21*x+m_r22*y);
}

TransformationAdapter::TransformationAdapter() : TransformationAdapter(1, 0, 0, 1) {}

TransformationAdapter::TransformationAdapter(int m11, int m12, int m21, int m22) :
    M_11(m11), M_12(m12),
    M_21(m21), M_22(m22) {}
