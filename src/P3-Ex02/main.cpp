#include "pch.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "DoubleBarrel.h"

using std::string;

int main(void)
{
    DoubleBarrel double_barrel(SuperShotgunState::BarrelFull);

    sf::RenderWindow window(sf::VideoMode(650, 400), "Double Barrel Shotgun");

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

    double_barrel.mActions[SuperShotgunState::BarrelFull] = std::bind(&DoubleBarrel::click, &double_barrel, std::placeholders::_1);
    double_barrel.mActions[SuperShotgunState::BarrelEmpty] = std::bind(&DoubleBarrel::reload, &double_barrel, std::placeholders::_1);

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

            double_barrel.readCommand(event);
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

