/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef LD_PRIVATEHELPERS_HPP
#define LD_PRIVATEHELPERS_HPP

#include <QXmlStreamReader>

namespace ld {
template<typename T>
void setPVar(T value, T* pvar = nullptr) {
    if(pvar != nullptr)
        *pvar = value;
}

inline void exitTag(const QStringRef& tagName, QXmlStreamReader& reader, int deep = 5) {
    while(reader.name() != tagName && deep-- >= 0)
        reader.skipCurrentElement();
}
}  // namespace ld

#endif  // LD_PRIVATEHELPERS_HPP
