#include "Collider.h"
#include "../../Interfaces/World.h"

#include "Entity.h"
#include <cmath>

void ColliderCircle::collision()
{

    Entity *p = dynamic_cast<Entity *>(getParent());
    if (!p)
        return;
    for (int i = 0; i < World::getObjectCount(); i++)
    {

        Object *obj = World::getObjectByIndex(i);
        if (obj == getParent())
            continue;
        if (obj->getColliderObject())
        {
            Collider *col;

            col = dynamic_cast<Collider *>(obj->getColliderObject());

            if (col)
            {
                if (col->getType() == COLLIDER_TYPE_LINE)
                {
                    ColliderLine *l = dynamic_cast<ColliderLine *>(col);

                    p->addImpulse(Collider::getMTVPolyCircle(l->getSide(), p->getWorldPos() + p->getVel(), getRadius()));
                }

                else if (col->getType() == COLLIDER_TYPE_RECT)
                {
                    ColliderRect *rect = dynamic_cast<ColliderRect *>(col);

                    p->addImpulse(Collider::getMTVPolyCircle(rect->getSides(), p->getWorldPos() + p->getVel(), getRadius()));
                }

                else if (col->getType() == COLLIDER_TYPE_CIRCLE)
                {
                    ColliderCircle *c = dynamic_cast<ColliderCircle *>(col);
                    SMath::vec2f h = (p->getWorldPos() + p->getVel()) - c->getWorldPos();
                    if (SMath::length(h) < getRadius() + c->getRadius())
                    {
                        SMath::vec2f mtv = SMath::normalize(h) * ((getRadius() + c->getRadius()) - SMath::length(h));

                        p->addImpulse(mtv);
                    }
                }
            }
        }
    }
}

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

collisionLinesResult Collider::checkCollisionLines(SMath::vec2f s1, SMath::vec2f e1, SMath::vec2f s2, SMath::vec2f e2)
{
    collisionLinesResult result;

    SMath::vec2f a = e1 - s1;
    SMath::vec2f b = e2 - s2;

    if (a.x != 0 && b.x != 0)
    {

        float k1 = a.y / a.x;
        float k2 = b.y / b.x;
        if (k1 == k2)
        {
            result.isColliding = false;
            return result;
        }
        float b1 = s1.y - k1 * s1.x;
        float b2 = s2.y - k2 * s2.x;
        float x = (b2 - b1) / (k1 - k2);
        float y = k1 * x + b1;
        if (x >= min(s1.x, e1.x) && x <= max(s1.x, e1.x) && x >= min(s2.x, e2.x) && x <= max(s2.x, e2.x))
        {
            result.isColliding = true;
            result.point = SMath::vec2f(x, y);
            return result;
        }
        result.isColliding = false;
        return result;
    }
    else
    {
        if (a.x == 0 && b.x != 0)
        {

            float x = s1.x;
            float k = b.y / b.x;
            float y = k * x + s2.y - k * s2.x;
            if (y >= min(s1.y, e1.y) && y <= max(s1.y, e1.y) && x >= min(s2.x, e2.x) && x <= max(s2.x, e2.x))
            {
                result.isColliding = true;
                result.point = SMath::vec2f(x, y);
                return result;
            }
        }
        else if (b.x == 0 && a.x != 0)
        {

            float x = s2.x;
            float k = a.y / a.x;
            float y = k * x + s1.y - k * s1.x;

            if (y >= min(s2.y, e2.y) && y <= max(s2.y, e2.y) && x >= min(s1.x, e1.x) && x <= max(s1.x, e1.x))
            {
                result.isColliding = true;
                result.point = SMath::vec2f(x, y);
                return result;
            }
        }
        else
        {
            result.isColliding = false;
            return result;
        }
    }
    result.isColliding = false;
    return result;
}
raycastResult Collider::raycast(SMath::vec2f s, SMath::vec2f e)
{
    return raycast(s, e, nullptr);
}
raycastResult Collider::raycast(SMath::vec2f s, SMath::vec2f e, Object *ignore)
{
    raycastResult result;

    for (int i = 0; i < World::getObjectCount(); i++)
    {

        Object *obj = World::getObjectByIndex(i);
        if (ignore && ignore == obj)
            continue;
        if (obj->getColliderObject())
        {
            Collider *col;

            col = dynamic_cast<Collider *>(obj->getColliderObject());

            if (col)
            {

                if (col->getType() == COLLIDER_TYPE_RECT)
                {

                    ColliderRect *rect = dynamic_cast<ColliderRect *>(col);

                    SMath::vec2f p1 = rect->getParent()->getPos();
                    SMath::vec2f p2 = rect->getParent()->getPos() + SMath::vec2f(rect->getSize().x, 0);
                    SMath::vec2f p3 = rect->getParent()->getPos() + rect->getSize();
                    SMath::vec2f p4 = rect->getParent()->getPos() + SMath::vec2f(0, rect->getSize().y);

                    collisionLinesResult res1 = checkCollisionLines(s, e, p1, p2);

                    collisionLinesResult res2 = checkCollisionLines(s, e, p2, p3);

                    collisionLinesResult res3 = checkCollisionLines(s, e, p3, p4);

                    collisionLinesResult res4 = checkCollisionLines(s, e, p4, p1);

                    if (res1.isColliding || res2.isColliding || res3.isColliding || res4.isColliding)
                    {
                        collidedObject colObj;
                        colObj.obj = obj;
                        if (res1.isColliding)
                            colObj.points.push_back(res1.point);
                        if (res2.isColliding)
                            colObj.points.push_back(res2.point);
                        if (res3.isColliding)
                            colObj.points.push_back(res3.point);
                        if (res4.isColliding)
                            colObj.points.push_back(res4.point);
                        result.isColliding = true;
                        result.collidedObjects.push_back(colObj);
                    }
                }
                else if (col->getType() == COLLIDER_TYPE_CIRCLE)
                {
                    collisionCircleResult res = checkCollisionLineWithCircle(s, e, col->getParent()->getPos(), dynamic_cast<ColliderCircle *>(col)->getRadius());
                    if (res.isColliding)
                    {
                        collidedObject colObj;
                        colObj.obj = obj;
                        colObj.points = res.points;
                        result.isColliding = true;
                        result.collidedObjects.push_back(colObj);
                    }
                }
            }
        }
    }
    return result;
}

collisionCircleResult Collider::checkCollisionLineWithCircle(SMath::vec2f s1, SMath::vec2f e1, SMath::vec2f c, float r)
{
    collisionCircleResult result;

    SMath::vec2f e2 = e1 - c;
    SMath::vec2f s2 = s1 - c;
    if (e2.x - s2.x == 0)
    {
        if (abs(s2.x) > r)
        {
            float y = sqrt(r * r - s2.x * s2.x);
            result.points.push_back(SMath::vec2f(s2.x, y) + c);
            if (y != 0)
            {
                result.points.push_back(SMath::vec2f(s2.x, -y) + c);
            }
            result.isColliding = false;
            return result;
        }
    }
    float k = (e2.y - s2.y) / (e2.x - s2.x);
    float b = s2.y - k * s2.x;

    float A = k * k + 1.f;
    float B = 2.f * k * b;
    float C = b * b - r * r;
    float D = B * B - 4.f * A * C;

    if (D < 0)
    {
        result.isColliding = false;
        return result;
    }
    float x1 = (-B + sqrt(D)) / (2.f * A);
    float x2 = (-B - sqrt(D)) / (2.f * A);
    float y1 = k * x1 + b;
    float y2 = k * x2 + b;
    x1 += c.x;
    x2 += c.x;
    y1 += c.y;
    y2 += c.y;
    if (x1 >= min(s1.x, e1.x) && x1 <= max(s1.x, e1.x) && y1 >= min(s1.y, e1.y) && y1 <= max(s1.y, e1.y))
    {
        result.isColliding = true;
        result.points.push_back(SMath::vec2f(x1, y1));
    }
    if (x2 >= min(s1.x, e1.x) && x2 <= max(s1.x, e1.x) && y2 >= min(s1.y, e1.y) && y2 <= max(s1.y, e1.y) && D != 0)
    {
        result.isColliding = true;
        result.points.push_back(SMath::vec2f(x2, y2));
    }
    return result;
}

collisionCircleResult Collider::checkCollisionLineWithCircle(SMath::side s, SMath::vec2f c, float r)
{
    return checkCollisionLineWithCircle(s.p1, s.p2, c, r);
}

SMath::vec2f Collider::getMTVPolyCircle(vector<SMath::side> sides, SMath::vec2f c, float r)
{
    SMath::vec2f m = sides[0].p1;
    float md = SMath::length(c, sides[0].p1);

    for (int i = 0; i < sides.size(); i++)
    {
        SMath::vec2f h;
        float t = SMath::scalar((c - sides[i].p1), (sides[i].p2 - sides[i].p1)) / SMath::pov(SMath::length((sides[i])), 2);
        if (t > 1)
        {
            h = sides[i].p2;
        }
        else if (t < 0)
        {
            h = sides[i].p1;
        }
        else
        {
            h = sides[i].p1 + (sides[i].p2 - sides[i].p1) * t;
        }
        float d = SMath::length(c, h);
        if (d < md)
        {
            md = d;
            m = h;
        }
    }
    if (md <= r)
    {
        SMath::vec2f mtv = SMath::normalize(c - m) * (r - md);
        return mtv;
    }
    return SMath::vec2f(0.f, 0.f);
}

SMath::vec2f Collider::getMTVPolyCircle(SMath::side s, SMath::vec2f c, float r)
{
    vector<SMath::side> v = {s};
    return getMTVPolyCircle(v, c, r);
}

SMath::side ColliderLine::getSide()
{
    if (getParent())
    {
        return s + getParent()->getWorldPos();
    }
    return s;
}
SMath::vec2f ColliderLine::getPoint1()
{
    if (getParent())
    {
        return s.p1 + getParent()->getWorldPos();
    }
    return s.p1;
}
SMath::vec2f ColliderLine::getPoint2()
{
    if (getParent())
    {
        return s.p2 + getParent()->getWorldPos();
    }
    return s.p2;
}
