#pragma once
#include "../Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Enemy : public Entity
{
public:
    void update() override {}
    Enemy() : Entity()
    {
        init();
    }
    Enemy(SMath::vec2f _pos) : Entity(_pos)
    {
        init();
    }

private:
    void init();
};