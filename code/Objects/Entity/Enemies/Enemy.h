#pragma once
#include "../Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Enemy : public Entity
{
public:
    void render(sf::RenderWindow &window) override;
    Enemy() : Entity()
    {
        init();
    }
    Enemy(sf::Vector2f _pos) : Entity(_pos)
    {
        init();
    }

private:
    sf::CircleShape shape;
    void init();
}; 