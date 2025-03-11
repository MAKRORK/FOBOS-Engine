#pragma once
#include "../Object.h"
#include <vector>
#include <iostream>
#include "../../Interfaces/SMath.h"
#include "../Camers/Camera.h"

// Ensure SMath namespace and vec2f type are defined

using namespace std;

#define COLLIDER_TYPE_CIRCLE 0
#define COLLIDER_TYPE_RECT 1
#define COLLIDER_TYPE_LINE 2

struct collisionLinesResult
{
    bool isColliding;
    SMath::vec2f point;
};
struct collisionCircleResult
{
    bool isColliding;
    vector<SMath::vec2f> points;
};
struct collidedObject
{
    Object *obj;
    vector<SMath::vec2f> points;
};
struct raycastResult
{
    bool isColliding;
    vector<collidedObject> collidedObjects;
};

class Collider : public Object
{
private:
    int type;

public:
    Collider() : Object() {}
    Collider(int _type) : Object() { type = _type; }
    Collider(SMath::vec2f _pos) : Object(_pos) {}
    Collider(SMath::vec2f _pos, int _type) : Object(_pos) { type = _type; }
    virtual void collision() {}
    int getType() { return type; }

    static collisionLinesResult checkCollisionLines(SMath::vec2f s1, SMath::vec2f e1, SMath::vec2f s2, SMath::vec2f e2);
    static raycastResult raycast(SMath::vec2f s, SMath::vec2f e);
    static raycastResult raycast(SMath::vec2f s, SMath::vec2f e, Object *ignore, bool draw = false, Camera *cam = nullptr);

    static collisionCircleResult checkCollisionLineWithCircle(SMath::vec2f s1, SMath::vec2f e1, SMath::vec2f c, float r);
    static collisionCircleResult checkCollisionLineWithCircle(SMath::side s, SMath::vec2f c, float r);
    static SMath::vec2f getMTVPolyCircle(vector<SMath::side> sides, SMath::vec2f c, float r);
    static SMath::vec2f getMTVPolyCircle(SMath::side s, SMath::vec2f c, float r);
};

class ColliderCircle : public Collider
{
private:
    float radius;

public:
    ColliderCircle(float _radius) : Collider(COLLIDER_TYPE_CIRCLE) { radius = _radius; }
    ColliderCircle(float _radius, SMath::vec2f _pos) : Collider(_pos, COLLIDER_TYPE_CIRCLE) { radius = _radius; }
    void collision() override;

    void setRadius(float _radius) { radius = _radius; }
    float getRadius() { return radius; }
};

class ColliderRect : public Collider
{
private:
    SMath::vec2f size;
    SMath::side sides[4] = {SMath::side(), SMath::side(), SMath::side(), SMath::side()};
    void init();

public:
    ColliderRect(SMath::vec2f _size) : Collider(COLLIDER_TYPE_RECT)
    {
        size = _size;
        init();
    }
    ColliderRect(SMath::vec2f _pos, SMath::vec2f _size) : Collider(_pos, COLLIDER_TYPE_RECT)
    {
        size = _size;
        init();
    }
    void collision() override;

    void setSize(SMath::vec2f _size) { size = _size; }
    SMath::vec2f getSize() { return size; }

    SMath::side getSide(int i);
    vector<SMath::side> getSides();
    SMath::vec2f getNormal(int i);
};

class ColliderLine : public Collider
{
private:
    SMath::side s;

public:
    ColliderLine(SMath::vec2f _p1, SMath::vec2f _p2) : Collider(COLLIDER_TYPE_LINE)
    {
        s.p1 = _p1;
        s.p2 = _p2;
    }
    ColliderLine(SMath::side _s) : Collider(COLLIDER_TYPE_LINE)
    {
        s = _s;
    }
    ColliderLine(SMath::vec2f _pos, SMath::vec2f _p1, SMath::vec2f _p2) : Collider(_pos, COLLIDER_TYPE_LINE)
    {
        s.p1 = _p1;
        s.p2 = _p2;
    }
    ColliderLine(SMath::vec2f _pos, SMath::side _s) : Collider(_pos, COLLIDER_TYPE_LINE)
    {
        s = _s;
    }
    void collision() override {}

    SMath::side getSide();

    SMath::vec2f getPoint1();
    SMath::vec2f getPoint2();
};
