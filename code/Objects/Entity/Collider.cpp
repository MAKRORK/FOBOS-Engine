#include "Collider.h"
#include "../../Interfaces/World.h"
#include "../../Interfaces/SMath.h"
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
        if (obj->getColliderObject())
        {
            Collider *col;

            col = dynamic_cast<Collider *>(obj->getColliderObject());

            if (col)
            {

                if (col->getType() == COLLIDER_TYPE_RECT)
                {

                    ColliderRect *rect = dynamic_cast<ColliderRect *>(col);

                    sf::Vector2f point[4];
                    point[0] = rect->getParent()->getPos();
                    point[1] = rect->getParent()->getPos() + sf::Vector2f(rect->getSize().x, 0);
                    point[2] = rect->getParent()->getPos() + rect->getSize();
                    point[3] = rect->getParent()->getPos() + sf::Vector2f(0, rect->getSize().y);

                    sf::Vector2f m = point[0];
                    float md = SMath::length((p->getWorldPos() + p->getVel()), point[0]);
                    for (int i = 1; i < 4; i++)
                    {
                        float l = SMath::length((p->getWorldPos() + p->getVel()), point[i]);
                        if (l < md)
                        {
                            m = point[i];
                            md = l;
                        }
                    }
                    if (md <= getRadius())
                    {
                        sf::Vector2f mtv = (getRadius() - md) * SMath::normalize(p->getWorldPos() - m);
                        p->addImpulse(mtv);
                    }

                    // collisionCircleResult res[4];
                    // for (int i = 0; i < 4; i++)
                    // {
                    //     // cout << rect->getSide(i).p1.x << " " << rect->getSide(i).p1.y << "    " << rect->getSide(i).p2.x << " " << rect->getSide(i).p2.y << endl;
                    //     res[i] = checkCollisionLineWithCircle(rect->getSide(i), p->getWorldPos() + p->getVel(), getRadius());
                    // }
                    // sf::Vector2f backVel = sf::Vector2f(0, 0);
                    // // cout << p->getVel().x << " " << p->getVel().y << "\n";
                    // for (int i = 0; i < 4; i++)
                    // {
                    //     if (res[i].isColliding)
                    //     {
                    //         // cout << getRadius() - SMath::distToLine(rect->getSide(i), p->getWorldPos() + p->getVel()) << endl;
                    //         sf::Vector2f normal = rect->getNormal(i);

                    //         backVel += normal * (getRadius() - SMath::distToLine(rect->getSide(i), p->getWorldPos() + p->getVel()));
                    //     }
                    // }
                    // p->addImpulse(backVel);

                    // res[0] = checkCollisionLineWithCircle(p1, p2, p->getWorldPos() + p->getVel(), getRadius());

                    // res[1] = checkCollisionLineWithCircle(p2, p3, p->getWorldPos() + p->getVel(), getRadius());

                    // res[2] = checkCollisionLineWithCircle(p3, p4, p->getWorldPos() + p->getVel(), getRadius());

                    // res[3] = checkCollisionLineWithCircle(p4, p1, p->getWorldPos() + p->getVel(), getRadius());
                }
            }
        }
    }
}

void ColliderRect::init()
{
    sf::Vector2f p1 = sf::Vector2f(0, 0);
    sf::Vector2f p2 = sf::Vector2f(0, 0) + sf::Vector2f(getSize().x, 0);
    sf::Vector2f p3 = sf::Vector2f(0, 0) + getSize();
    sf::Vector2f p4 = sf::Vector2f(0, 0) + sf::Vector2f(0, getSize().y);
    sides[0] = side{p1, p2};
    sides[1] = side{p2, p3};
    sides[2] = side{p3, p4};
    sides[3] = side{p4, p1};
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

side ColliderRect::getSide(int i)
{
    if (!getParent())
        return sides[i];
    return sides[i] + getParent()->getPos();
}

sf::Vector2f ColliderRect::getNormal(int i)
{
    if (i == 0)
    {
        return sf::Vector2f(0, -1);
    }
    if (i == 1)
    {
        return sf::Vector2f(1, 0);
    }
    if (i == 2)
    {
        return sf::Vector2f(0, 1);
    }
    if (i == 3)
    {
        return sf::Vector2f(-1, 0);
    }
    return sf::Vector2f(0, 0);
}

collisionLinesResult Collider::checkCollisionLines(sf::Vector2f s1, sf::Vector2f e1, sf::Vector2f s2, sf::Vector2f e2)
{
    collisionLinesResult result;

    sf::Vector2f a = e1 - s1;
    sf::Vector2f b = e2 - s2;

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
            result.point = sf::Vector2f(x, y);
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
                result.point = sf::Vector2f(x, y);
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
                result.point = sf::Vector2f(x, y);
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

raycastResult Collider::raycast(sf::Vector2f s, sf::Vector2f e)
{
    raycastResult result;

    for (int i = 0; i < World::getObjectCount(); i++)
    {

        Object *obj = World::getObjectByIndex(i);
        if (obj->getColliderObject())
        {
            Collider *col;

            col = dynamic_cast<Collider *>(obj->getColliderObject());

            if (col)
            {

                if (col->getType() == COLLIDER_TYPE_RECT)
                {

                    ColliderRect *rect = dynamic_cast<ColliderRect *>(col);

                    sf::Vector2f p1 = rect->getParent()->getPos();
                    sf::Vector2f p2 = rect->getParent()->getPos() + sf::Vector2f(rect->getSize().x, 0);
                    sf::Vector2f p3 = rect->getParent()->getPos() + rect->getSize();
                    sf::Vector2f p4 = rect->getParent()->getPos() + sf::Vector2f(0, rect->getSize().y);

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

collisionCircleResult Collider::checkCollisionLineWithCircle(sf::Vector2f s1, sf::Vector2f e1, sf::Vector2f c, float r)
{
    collisionCircleResult result;

    sf::Vector2f e2 = e1 - c;
    sf::Vector2f s2 = s1 - c;
    if (e2.x - s2.x == 0)
    {
        if (abs(s2.x) > r)
        {
            float y = sqrt(r * r - s2.x * s2.x);
            result.points.push_back(sf::Vector2f(s2.x, y) + c);
            if (y != 0)
            {
                result.points.push_back(sf::Vector2f(s2.x, -y) + c);
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
        result.points.push_back(sf::Vector2f(x1, y1));
    }
    if (x2 >= min(s1.x, e1.x) && x2 <= max(s1.x, e1.x) && y2 >= min(s1.y, e1.y) && y2 <= max(s1.y, e1.y) && D != 0)
    {
        result.isColliding = true;
        result.points.push_back(sf::Vector2f(x2, y2));
    }
    return result;
}

collisionCircleResult Collider::checkCollisionLineWithCircle(side s, sf::Vector2f c, float r)
{
    return checkCollisionLineWithCircle(s.p1, s.p2, c, r);
}
