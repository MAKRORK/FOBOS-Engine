#pragma once
#include "../Entity.h"

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