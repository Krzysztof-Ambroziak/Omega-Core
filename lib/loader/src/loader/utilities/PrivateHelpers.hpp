/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_PRIVATEHELPERS_HPP
#define LD_PRIVATEHELPERS_HPP

namespace ld {
template<typename T>
void setPVar(T value, T* pvar = nullptr) {
    if(pvar != nullptr)
        *pvar = value;
}
}  // namespace ld

#endif  // LD_PRIVATEHELPERS_HPP
