#include "../Camers/Camera.h"
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
    void update() override;
    void movement(float delta);

private:
    float speed = 200.f;
    void init();
};