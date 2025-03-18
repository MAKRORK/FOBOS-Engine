#include "ColliderRect.h"
#include "../../../Interfaces/World.h"

void ColliderRect::init()
{
    SMath::vec2f p1 = SMath::vec2f(0, 0);
    SMath::vec2f p2 = SMath::vec2f(0, 0) + SMath::vec2f(getSize().x, 0);
    SMath::vec2f p3 = SMath::vec2f(0, 0) + getSize();
    SMath::vec2f p4 = SMath::vec2f(0, 0) + SMath::vec2f(0, getSize().y);
    sides[0] = SMath::side{p1, p2};
    sides[1] = SMath::side{p2, p3};
    sides[2] = SMath::side{p3, p4};
    sides[3] = SMath::side{p4, p1};
    updateCircle();
}

void ColliderRect::updateCircle()
{
    setCircleCenter(getSize() / 2.f);
    setCircleRad(SMath::length(getSize() / 2.f));
    setRect(0.f, getSize());
}

void ColliderRect::collision()
{
    for (int i = 0; i < World::getObjectCount(); i++)
    {
        Object *obj = World::getObjectByIndex(i);
        if (obj && obj != this)
        {
            Collider *col = dynamic_cast<Collider *>(obj->getColliderObject());
            if (col)
            {
            }
        }
    }
}

SMath::side ColliderRect::getSide(int i)
{
    if (!getParent())
        return sides[i];
    return sides[i] + getParent()->getPos();
}

vector<SMath::side> ColliderRect::getSides()
{
    vector<SMath::side> s;
    for (int i = 0; i < 4; i++)
    {
        s.push_back(getSide(i));
    }
    return s;
}

SMath::vec2f ColliderRect::getNormal(int i)
{
    if (i == 0)
    {
        return SMath::vec2f(0, -1);
    }
    if (i == 1)
    {
        return SMath::vec2f(1, 0);
    }
    if (i == 2)
    {
        return SMath::vec2f(0, 1);
    }
    if (i == 3)
    {
        return SMath::vec2f(-1, 0);
    }
    return SMath::vec2f(0, 0);
}