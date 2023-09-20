/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef DP_OBSERVER_HPP
#define DP_OBSERVER_HPP

namespace dp {
template<typename T>
class Observer {
public:
    virtual void update(const T& arg) = 0;
};
}

#endif  // DP_OBSERVER_HPP
