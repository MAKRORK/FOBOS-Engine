#include "Object.h"
#include "Entity/Collider.h"
#include "../Visual/Shape.h"
#include <cmath>

Object::Object()
{
    pos = SMath::vec2f(0.f, 0.f);
    rot = 0.f;
}

Object::Object(SMath::vec2f _pos)
{
    pos = _pos;
    rot = 0.f;
}

Object::~Object()
{
    for (Object *child : childrens)
    {
        delete child;
    }
    childrens.clear();
}

void Object::setPos(SMath::vec2f _pos)
{
    pos = _pos;
}
void Object::setRot(float _rot)
{
    rot = _rot;
}

void Object::addPos(SMath::vec2f _pos)
{
    pos += _pos;
}

void Object::addRot(float _rot)
{
    rot += _rot;
}

float Object::getScale()
{
    return scale;
}

float Object::getWorldScale()
{
    if (parent)
    {
        return scale * parent->getWorldScale();
    }
    return scale;
}

void Object::setScale(float _s)
{
    scale = _s;
}

SMath::vec2f Object::getPos()
{
    return pos;
}
float Object::getRot()
{
    return rot;
}
SMath::vec2f Object::getWorldPos()
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

int Object::addChildren(Object *child)
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
    return childrens.size() - 1;
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

Object *Object::getChildrenByIndex(int i)
{
    return childrens[i];
}

std::vector<Object *> Object::getChildrens()
{
    return childrens;
}

vector<Object *> Object::getShapes()
{
    vector<Object *> s;
    for (int i = 0; i < childrens.size(); i++)
    {
        if (dynamic_cast<Shape *>(childrens[i]))
        {
            s.push_back(childrens[i]);
        }
    }
    return s;
}

SMath::vec2f Object::getForwardVector()
{
    return SMath::vec2f(cosf(getWorldRot()), sinf(getWorldRot()));
}
