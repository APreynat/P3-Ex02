#pragma once
#include <SFML/Graphics.hpp>

class DoubleBarrel;

class Action {
protected:
    DoubleBarrel* mSuperShotgun;

public:

    Action(DoubleBarrel* super_shotgun) : mSuperShotgun(super_shotgun) {}

    virtual void Update(sf::Event& input) = 0;

    virtual ~Action() {}
};
