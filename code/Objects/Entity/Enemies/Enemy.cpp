#include "Enemy.h"
#include "../Collider.h"

void Enemy::render(sf::RenderWindow &window)
{
    shape.setPosition(getPos() - sf::Vector2f(15.f, 15.f));
    window.draw(shape);
}
void Enemy::init()
{
    shape.setRadius(15.f);
    shape.setFillColor(sf::Color::Blue);
    // addChildren(new ColliderCircle(10.f));
}