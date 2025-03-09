#pragma once
#include "../Object.h"
class Entity : public Object
{
public:
    virtual void physics(float delta);
    void render() {}
    Entity() : Object() {}
    Entity(sf::Vector2f _pos) : Object(_pos) {}
    void setColliding(bool _isColliding);
    bool getColliding();

    sf::Vector2f getVel();
    void addImpulse(sf::Vector2f impulse);

protected:
    sf::Vector2f vel = sf::Vector2f(0.f, 0.f);

private:
    bool isColliding = false;
};