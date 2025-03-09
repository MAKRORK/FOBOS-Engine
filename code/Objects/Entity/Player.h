#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "Entity.h"
#include <iostream>

class Player : public Entity
{
public:
    Player() : Entity()
    {
        init();
    }
    Player(sf::Vector2f _pos) : Entity(_pos)
    {
        init();
    }
    void render(sf::RenderWindow &window) override;
    void movement(float delta);

private:
    sf::CircleShape shape;
    float speed = 200.f;
    void init();
};