/*
Copyright (c) 2023 Krzysztof Ambroziak
*/

#ifndef UPDATESERVICE_HPP
#define UPDATESERVICE_HPP

#include "api/IUpdateService.hpp"

class InputEventModel;

class UpdateService : public IUpdateService {
public:
    UpdateService(InputEventModel* inputEventModel);
    
    void update(int dt) override;

private:
    InputEventModel* const m_inputEventModel;
};

#endif // UPDATESERVICE_HPP
