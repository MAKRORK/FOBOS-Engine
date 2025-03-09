#include "Object.h"
#include "Entity/Collider.h"
#include <cmath>

Object::Object()
{
    pos = sf::Vector2f(0.f, 0.f);
    rot = 0.f;
}

Object::Object(sf::Vector2f _pos)
{
    pos = _pos;
    rot = 0.f;
}

void Object::setPos(sf::Vector2f _pos)
{
    pos = _pos;
}
void Object::setRot(float _rot)
{
    rot = _rot;
}

void Object::addPos(sf::Vector2f _pos)
{
    pos += _pos;
}

void Object::addRot(float _rot)
{
    rot += _rot;
}

sf::Vector2f Object::getPos()
{
    return pos;
}
float Object::getRot()
{
    return rot;
}
sf::Vector2f Object::getWorldPos()
{
    if (parent)
    {
        return parent->getWorldPos() + pos;
    }
    return pos;
}
float Object::getWorldRot()
{
    if (parent)
    {
        return parent->getWorldRot() + rot;
    }
    return rot;
}

void Object::addChildren(Object *child)
{
    if (child)
    {
        child->setParent(this);
        if (!collider)
        {
            if (dynamic_cast<Collider *>(child))
            {
                collider = child;
            }
        }
    }
    childrens.push_back(child);
}

void Object::setParent(Object *_parent)
{
    parent = _parent;
}
Object *Object::getParent()
{
    return parent;
}

Object *Object::getColliderObject()
{
    return collider;
}

sf::Vector2f Object::getForwardVector()
{
    return sf::Vector2f(cosf(getWorldRot()), sinf(getWorldRot()));
}
