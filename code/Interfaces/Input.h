#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "SMath.h"

class Input
{
private:
    static SMath::vec2 previusMousePos;
    static SMath::vec2 delta;
    static bool centered;

public:
    static void init();
    static void update();
    static bool isPressed(sf::Keyboard::Key key);
    static bool justPressed(sf::Keyboard::Key key);
    static SMath::vec2 getMousePos();
    static SMath::vec2 getMouseDelta();
    static void setMouseCentered(bool c);
    static bool getMouseCentered();
};
