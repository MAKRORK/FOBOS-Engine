#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../../Interfaces/SMath.h"
#include "Entity.h"
#include <iostream>

class Player : public Entity
{
public:
    Player() : Entity()
    {
        init();
    }
    Player(SMath::vec2f _pos) : Entity(_pos)
    {
        init();
    }
    void render(sf::RenderWindow &window);
    void update() override {}
    void movement(float delta);

private:
    float speed = 200.f;
    void init();
};