#pragma once
#include "Action.h"

class DoubleBarrel;

class Shoot_Action : public Action {
public:
    Shoot_Action(DoubleBarrel* super_shotgun) : Action(super_shotgun) {}

    void Update(sf::Event& input) override;
};
