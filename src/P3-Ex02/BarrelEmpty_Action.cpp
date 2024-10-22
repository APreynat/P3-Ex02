#include "pch.h"
#include "BarrelEmpty_Action.h"
#include "DoubleBarrel.h"

constexpr int G_RELOAD_TIME = 3;

void BarrelEmpty_Action::Update(sf::Event& input) {
    if (input.type == sf::Event::KeyPressed && input.key.code == sf::Keyboard::R)
    {
        mSuperShotgun->SetState = new (SuperShotgunState::Reloading);
        std::thread start_thread(&DoubleBarrel::_reloadCounter, this);
        start_thread.detach();
    }
}

void BarrelEmpty_Action::_reloadCounter()
{
    std::this_thread::sleep_for(std::chrono::seconds(G_RELOAD_TIME));
    mSuperShotgun->state = SuperShotgunState::BarrelFull;
}