#include "Wall.h"
#include <iostream>
#include "../Entity/Collider.h"

void Wall::init()
{
    rect.setSize(sf::Vector2f(32.f, 32.f));
    rect.setPosition(getPos());
    rect.setFillColor(sf::Color::White);
    addChildren(new ColliderRect(sf::Vector2f(32.f, 32.f)));
}

void Wall::render(sf::RenderWindow &window)
{
    window.draw(rect);
}
