/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef IUPDATESERVICE_HPP
#define IUPDATESERVICE_HPP

class IUpdateService {
public:
    virtual void update(int dt) = 0;
};

#endif  // IUPDATESERVICE_HPP
