#include "pch.h"
#include "main.h"

#include <chrono>
#include <iostream>
#include <thread>
#include <map>
#include <functional>
#include <SFML/Graphics.hpp>

using std::string;

#define COOLPURPLE \
    CLITERAL(Color) { 153, 0, 0, 255 }  // cool Purple

constexpr int G_RELOAD_TIME = 3;

enum class SuperShotgunState
{
    BarrelFull,
    BarrelEmpty,
    Reloading
};

typedef struct DoubleBarrel
{
    SuperShotgunState state;

    void click()
    {
        switch (this->state)
        {
        case SuperShotgunState::BarrelFull:
        {
            this->state = SuperShotgunState::BarrelEmpty;
            break;
        }
        case SuperShotgunState::BarrelEmpty:
            break;
        case SuperShotgunState::Reloading:
            break;
        }
    }

    void reload()
    {
        switch (this->state)
        {
        case SuperShotgunState::BarrelFull:
            break;
        case SuperShotgunState::BarrelEmpty:
        {
            this->state = SuperShotgunState::Reloading;
            std::thread start_thread(&DoubleBarrel::_reloadCounter, this);
            start_thread.detach();
            break;
        }
        case SuperShotgunState::Reloading:
            break;
        }
    }

    SuperShotgunState getState()
    {
        return this->state;
    }

    string getStateStr()
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

private:

    void _reloadCounter()
    {
        std::this_thread::sleep_for(std::chrono::seconds(G_RELOAD_TIME));
        this->state = SuperShotgunState::BarrelFull;
    }

} DoubleBarrel;


std::map<SuperShotgunState, std::function<void(sf::Event&)>> mActions;

DoubleBarrel double_barrel{ SuperShotgunState::BarrelFull };

void readCommand(sf::Event& input)
{
    auto currentState = double_barrel.getState();
    if (mActions.find(currentState) != mActions.end())
    {
        mActions[currentState](input); // Call the action for the current state
    }
}

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(650, 400), "GamingCampus - SuperShotgunVisualizer");

    string barrel_empty_path = "../../../images/BarrelEmpty.png";
    string barrel_full_path = "../../../images/BarrelFull.png";
    string clicking_path = "../../../images/Clicking.png";
    string reloading_path = "../../../images/Reloading.png";
    sf::Texture barrel_empty_texture;
    sf::Texture barrel_full_texture;
    sf::Texture clicking_texture;
    sf::Texture reloading_texture;

    if (!barrel_empty_texture.loadFromFile(barrel_empty_path))
    {
        std::cerr << "Failed to load barrel_empty_texture" << std::endl;
        return -1;
    }
    if (!barrel_full_texture.loadFromFile(barrel_full_path))
    {
        std::cerr << "Failed to load barrel_full_texture" << std::endl;
        return -1;
    }
    if (!clicking_texture.loadFromFile(clicking_path))
    {
        std::cerr << "Failed to load clicking_texture" << std::endl;
        return -1;
    }
    if (!reloading_texture.loadFromFile(reloading_path))
    {
        std::cerr << "Failed to load reloading_texture" << std::endl;
        return -1;
    }

    sf::Sprite barrel_empty_sprite(barrel_empty_texture);
    sf::Sprite barrel_full_sprite(barrel_full_texture);
    sf::Sprite clicking_sprite(clicking_texture);
    sf::Sprite reloading_sprite(reloading_texture);

    barrel_empty_sprite.setScale(0.52f, 0.56f);
    barrel_full_sprite.setScale(0.52f, 0.56f);
    clicking_sprite.setScale(0.52f, 0.56f);
    reloading_sprite.setScale(0.52f, 0.56f);

    barrel_empty_sprite.setPosition(0, 0);
    barrel_full_sprite.setPosition(0, 0);
    clicking_sprite.setPosition(0, 0);
    reloading_sprite.setPosition(0, 0);

    sf::Font font;
    if (!font.loadFromFile("../../../.fonts/Hack-Regular.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    sf::Text stateText;
    stateText.setFont(font);
    stateText.setCharacterSize(36);
    stateText.setFillColor(sf::Color::White);
    stateText.setPosition(10, 10);

    // Define actions for each state
    mActions[SuperShotgunState::BarrelFull] = [&](sf::Event& input)
        {
            if (input.type == sf::Event::MouseButtonPressed && input.mouseButton.button == sf::Mouse::Left)
            {
                double_barrel.click();
            }
        };

    mActions[SuperShotgunState::BarrelEmpty] = [&](sf::Event& input)
        {
            if (input.type == sf::Event::KeyPressed && input.key.code == sf::Keyboard::R)
            {
                double_barrel.reload();
            }
        };


    // loop :
    // - print state each second.
    // - get user input: Click/Reload/Quit
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }

            readCommand(event); // Call the new readCommand function
        }

        stateText.setString(double_barrel.getStateStr());

        switch (double_barrel.getState())
        {
        case SuperShotgunState::BarrelFull:
            window.draw(barrel_full_sprite);
            break;
        case SuperShotgunState::BarrelEmpty:
            window.draw(barrel_empty_sprite);
            break;
        case SuperShotgunState::Reloading:
            window.draw(reloading_sprite);
            break;
        }

        window.draw(stateText);
        window.display();
    }
    return 0;
}
