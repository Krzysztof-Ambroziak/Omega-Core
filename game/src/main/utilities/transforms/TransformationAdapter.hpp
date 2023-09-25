/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef TRANSFORMATIONADAPTER_HPP
#define TRANSFORMATIONADAPTER_HPP

#include "ITransformation.hpp"

class TransformationAdapter : public ITransformation {
public:
    QPointF transform(const QPoint& point) const override;

protected:
    TransformationAdapter();
    
    TransformationAdapter(int m11, int m12, int m21, int m22);

protected:
    const int M_11, M_12,
              M_21, M_22;
    
    double m_r11, m_r12,
           m_r21, m_r22;
};

#endif  // TRANSFORMATIONADAPTER_HPP
