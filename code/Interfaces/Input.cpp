#include "Input.h"
#include "Render.h"
#include "ForSFML.h"

SMath::vec2 Input::previusMousePos;
SMath::vec2 Input::delta;
bool Input::centered = false;

void Input::init()
{
    previusMousePos = getMousePos();
}

void Input::update()
{
    SMath::vec2 p = getMousePos();
    delta = p - previusMousePos;
    if (centered)
    {
        previusMousePos = Render::getWindowCord() + (Render::getWindowSize() / 2);
        sf::Mouse::setPosition(forSFML::toSFMLVectorI(previusMousePos));
    }
    else
        previusMousePos = p;
}

bool Input::isPressed(sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}

bool Input::justPressed(sf::Keyboard::Key key)
{
    return false;
}

SMath::vec2 Input::getMousePos()
{
    return Render::getWindowCord(forSFML::fromSFMLVectorI(sf::Mouse::getPosition()));
}

SMath::vec2 Input::getMouseDelta()
{
    return delta;
}

void Input::setMouseCentered(bool c)
{
    centered = c;
}

bool Input::getMouseCentered()
{
    return centered;
}
