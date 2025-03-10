#pragma once
#include "../Object.h"
#include "../../Interfaces/SMath.h"
class Entity : public Object
{
public:
    virtual void physics(float delta);
    void update() override {}
    Entity() : Object() {}
    Entity(SMath::vec2f _pos) : Object(_pos) {}
    void setColliding(bool _isColliding);
    bool getColliding();

    SMath::vec2f getVel();
    void addImpulse(SMath::vec2f impulse);

protected:
    SMath::vec2f vel = SMath::vec2f(0.f, 0.f);

private:
    bool isColliding = false;
};