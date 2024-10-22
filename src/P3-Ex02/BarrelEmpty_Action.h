#pragma once
#include "Action.h"

class DoubleBarrel;

class BarrelEmpty_Action : public Action {
public:
    BarrelEmpty_Action(DoubleBarrel* super_shotgun) : Action(super_shotgun) {}

    void Update(sf::Event& input) override;

    void _reloadCounter();
};