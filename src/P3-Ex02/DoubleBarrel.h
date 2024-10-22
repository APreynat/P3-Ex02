#pragma once
#include "pch.h"

enum class SuperShotgunState
{
    BarrelFull,
    BarrelEmpty,
    Reloading
};

class DoubleBarrel {
protected:

    Action* currentAction;

public:
    DoubleBarrel(SuperShotgunState initialState);

    void click(sf::Event& input);
    void reload(sf::Event& input);
    SuperShotgunState getState();
    std::string getStateStr();
    void readCommand(sf::Event& input);

    void SetState(Action* new_action);

    std::map<SuperShotgunState, std::function<void(sf::Event&)>> mActions;

private:
    SuperShotgunState state;
    void _reloadCounter();
};