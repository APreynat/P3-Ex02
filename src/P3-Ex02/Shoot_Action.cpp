#include "pch.h"
#include "Shoot_Action.h"
#include "DoubleBarrel.h"


void Shoot_Action::Update(sf::Event& input) {
    if (input.type == sf::Event::MouseButtonPressed && input.mouseButton.button == sf::Mouse::Left) {
        // Check if the barrel is already empty
        if (mSuperShotgun->getState() == SuperShotgunState::BarrelEmpty) {
            std::cout << "Click! (Barrel is empty)\n"; // Empty barrel feedback
        }
        else {
            // Fire a shot
            std::cout << "Bang! (Shot fired)\n";
            // Transition to BarrelEmpty state
            mSuperShotgun->SetState(new BarrelEmpty_Action(mSuperShotgun));
        }
    }
}