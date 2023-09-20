/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef DP_OBSERVABLE_HPP
#define DP_OBSERVABLE_HPP

#include "Observer.hpp"

#include <forward_list>

namespace dp {
template <typename T>
class Observable {
public:
    void addObserver(Observer<T>* const observer) {
        m_observers.push_front(observer);
    }
    
    void removeObserver(Observer<T>* const observer) {
        m_observers.remove(observer);
    }
    
    void removeObservers() {
        m_observers.clear();
    }
    
    void notifyObservers(const T& arg) {
        for(auto& o: m_observers)
            o->update(arg);
    }

private:
    std::forward_list<Observer<T>*> m_observers;
};
}

#endif  // DP_OBSERVABLE_HPP
