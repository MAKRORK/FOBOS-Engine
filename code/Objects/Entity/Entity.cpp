#include "Entity.h"
#include "Collider.h"

void Entity::physics(float delta)
{
    if (getColliderObject())
    {
        Collider *col = dynamic_cast<Collider *>(getColliderObject());
        col->collision();
    }
    addPos(vel);
    vel = sf::Vector2f(0.f, 0.f);
}

void Entity::setColliding(bool _isColliding)
{
    isColliding = _isColliding;
}

bool Entity::getColliding()
{
    return isColliding;
}

sf::Vector2f Entity::getVel()
{
    return vel;
}

void Entity::addImpulse(sf::Vector2f impulse)
{
    vel += impulse;
}
