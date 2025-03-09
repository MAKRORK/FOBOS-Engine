#pragma once
#include <SFML/Window/Keyboard.hpp>
class Input
{
public:
    static bool isPressed(sf::Keyboard::Key key);
    static bool justPressed(sf::Keyboard::Key key);
};
