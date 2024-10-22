#include "pch.h"
#include "Reload_Action.h"
#include "DoubleBarrel.h"

void Reload_Action::Update(sf::Event& input) {
    // Check for reload input (R key press)
    if (input.type == sf::Event::KeyPressed && input.key.code == sf::Keyboard::R) {
        // Handle reload feedback (e.g., play reload sound)
        std::cout << "Reloading...\n";

        // Simulate reloading time (you could use a delay or threading)
        std::this_thread::sleep_for(std::chrono::seconds(2));  // Simulating reload delay

        // Set the state back to BarrelFull after reload
        mSuperShotgun->SetState(new Shoot_Action(mSuperShotgun));
        std::cout << "Reload complete. Ready to fire!\n";
    }
}