#pragma once
#include "SFML/System/Vector2.hpp"
#include "../Object.h"
#include <vector>
#include <iostream>

using namespace std;

#define COLLIDER_TYPE_CIRCLE 0
#define COLLIDER_TYPE_RECT 1

struct collisionLinesResult
{
    bool isColliding;
    sf::Vector2f point;
};
struct collisionCircleResult
{
    bool isColliding;
    vector<sf::Vector2f> points;
};
struct collidedObject
{
    Object *obj;
    vector<sf::Vector2f> points;
};
struct raycastResult
{
    bool isColliding;
    vector<collidedObject> collidedObjects;
};

struct side
{
    sf::Vector2f p1;
    sf::Vector2f p2;
    side() : p1(sf::Vector2f(0, 0)), p2(sf::Vector2f(0, 0)) {}
    side(sf::Vector2f _p1, sf::Vector2f _p2) : p1(_p1), p2(_p2) {}
    side operator+(sf::Vector2f v)
    {
        return side{p1 + v, p2 + v};
    }
};

class Collider : public Object
{
private:
    int type;

public:
    Collider() : Object() {}
    Collider(int _type) : Object() { type = _type; }
    Collider(sf::Vector2f _pos) : Object(_pos) {}
    Collider(sf::Vector2f _pos, int _type) : Object(_pos) { type = _type; }
    virtual void collision() {}
    int getType() { return type; }

    static collisionLinesResult checkCollisionLines(sf::Vector2f s1, sf::Vector2f e1, sf::Vector2f s2, sf::Vector2f e2);
    static raycastResult raycast(sf::Vector2f s, sf::Vector2f e);
    static collisionCircleResult checkCollisionLineWithCircle(sf::Vector2f s1, sf::Vector2f e1, sf::Vector2f c, float r);
    static collisionCircleResult checkCollisionLineWithCircle(side s, sf::Vector2f c, float r);
};

class ColliderCircle : public Collider
{
private:
    float radius;

public:
    ColliderCircle(float _radius) : Collider(COLLIDER_TYPE_CIRCLE) { radius = _radius; }
    ColliderCircle(float _radius, sf::Vector2f _pos) : Collider(_pos, COLLIDER_TYPE_CIRCLE) { radius = _radius; }
    void collision() override;

    void setRadius(float _radius) { radius = _radius; }
    float getRadius() { return radius; }
};

class ColliderRect : public Collider
{
private:
    sf::Vector2f size;
    side sides[4] = {side(), side(), side(), side()};
    void init();

public:
    ColliderRect(sf::Vector2f _size) : Collider(COLLIDER_TYPE_RECT)
    {
        size = _size;
        init();
    }
    ColliderRect(sf::Vector2f _pos, sf::Vector2f _size) : Collider(_pos, COLLIDER_TYPE_RECT)
    {
        size = _size;
        init();
    }
    void collision() override;

    void setSize(sf::Vector2f _size) { size = _size; }
    sf::Vector2f getSize() { return size; }

    side getSide(int i);
    sf::Vector2f getNormal(int i);
};
