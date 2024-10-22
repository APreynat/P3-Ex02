#include "pch.h"
#include "DoubleBarrel.h"

DoubleBarrel::DoubleBarrel(SuperShotgunState initialState) : state(initialState) {}

//void DoubleBarrel::click(sf::Event& input)
//{
//    if (input.type == sf::Event::MouseButtonPressed && input.mouseButton.button == sf::Mouse::Left)
//    {
//        this->state = SuperShotgunState::BarrelEmpty;
//    }
//}

//void DoubleBarrel::reload(sf::Event& input)
//{
//    if (input.type == sf::Event::KeyPressed && input.key.code == sf::Keyboard::R)
//    {
//        this->state = SuperShotgunState::Reloading;
//        std::thread start_thread(&DoubleBarrel::_reloadCounter, this);
//        start_thread.detach();
//    }
//}

SuperShotgunState DoubleBarrel::getState()
{
    return this->state;
}

std::string DoubleBarrel::getStateStr()
{
    switch (this->state)
    {
    case SuperShotgunState::BarrelFull:
        return "BarrelFull";
    case SuperShotgunState::BarrelEmpty:
        return "BarrelEmpty";
    case SuperShotgunState::Reloading:
        return "Reloading";
    default:
        return "something went horribly wrong";
    }
}

void DoubleBarrel::readCommand(sf::Event& input)
{
    if (mActions.find(this->state) != mActions.end())
    {
        mActions[this->state](input);
    }
}


void DoubleBarrel::SetState(Action* new_action) {
    currentAction = new_action; // Set the new action
    currentAction->Start();     // Optionally call Start method
}