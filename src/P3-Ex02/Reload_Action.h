#pragma once
#include "Action.h"

class DoubleBarrel;

class Reload_Action : public Action {
public:
    Reload_Action(DoubleBarrel* super_shotgun) : Action(super_shotgun) {}

    void Update(sf::Event& input) override;
};