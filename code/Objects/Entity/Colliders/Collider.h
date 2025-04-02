#pragma once
#include "../../Object.h"
#include <vector>
#include <iostream>
#include "../../../Interfaces/SMath.h"
#include "../../Camers/Camera.h"
#include "../../../Algoritms/GeometryAlgoritms.h"
#include "../../../Primitives/Primitives2D.h"

// Ensure SMath namespace and vec2f type are defined

using namespace std;

#define COLLIDER_TYPE_CIRCLE 0
#define COLLIDER_TYPE_RECT 1
#define COLLIDER_TYPE_LINE 2
#define COLLIDER_TYPE_POLY 3

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
    Object *obj = nullptr;
    vector<SMath::vec2f> points;
    vector<int> sides;
};
struct raycastResult
{
    bool isColliding;
    vector<collidedObject> collidedObjects;
};
class BVH;

class Collider : public Object
{
private:
    int type;
    float radiusCircle;
    SMath::vec2f centerCircle;
    SMath::Geometry::RectGeometry rect;
    bool isDynamic = false;
    bool isTriger = false;

protected:
    void setCircleRad(float _r) { radiusCircle = _r; }
    void setCircleCenter(SMath::vec2f _c) { centerCircle = _c; }
    void setRect(SMath::vec2f _tl, SMath::vec2f _br);
    static vector<Collider *> colliders;
    static vector<Collider *> statics;
    static vector<Collider *> dynamics;
    static BVH *bvh;

public:
    Collider() : Object() { colliders.push_back(this); }
    Collider(int _type) : Object()
    {
        type = _type;
        colliders.push_back(this);
        statics.push_back(this);
    }
    Collider(SMath::vec2f _pos) : Object(_pos) { colliders.push_back(this); }
    Collider(SMath::vec2f _pos, int _type) : Object(_pos)
    {
        type = _type;
        colliders.push_back(this);
        statics.push_back(this);
    }
    virtual ~Collider();
    virtual void collision() {}
    int getType() { return type; }

    float getRadiusCircle() { return radiusCircle; }
    SMath::vec2f getCenterCircle() { return centerCircle; }

    SMath::vec2f getTopLeft() { return rect.tl + getWorldPos(); }
    SMath::vec2f getButtomRigth() { return rect.br + getWorldPos(); }

    static collisionLinesResult checkCollisionLines(SMath::vec2f s1, SMath::vec2f e1, SMath::vec2f s2, SMath::vec2f e2);
    static raycastResult raycast(SMath::vec2f s, SMath::vec2f e);
    static raycastResult raycast(SMath::vec2f s, SMath::vec2f e, Object *ignore, bool draw = false, Camera *cam = nullptr);
    static raycastResult raycastForThread(SMath::vec2f s, SMath::vec2f e, vector<Collider *> colls);

    static collisionCircleResult checkCollisionLineWithCircle(SMath::vec2f s1, SMath::vec2f e1, SMath::vec2f c, float r);
    static collisionCircleResult checkCollisionLineWithCircle(SMath::side s, SMath::vec2f c, float r);
    static collisionCircleResult intersectLineCircle(const SMath::vec2f &p1, const SMath::vec2f &p2, const SMath::vec2f &center, float radius);
    static SMath::vec2f getMTVPolyCircle(vector<SMath::side> sides, SMath::vec2f c, float r);
    static SMath::vec2f getMTVPolyCircle(SMath::side s, SMath::vec2f c, float r);
    static vector<Collider *> getCollidersInBVH(SMath::Geometry::RectGeometry rect, Object *ignore);
    static collisionLinesResult checkLineIntersection(const SMath::vec2f &A, const SMath::vec2f &B,
                                                      const SMath::vec2f &C, const SMath::vec2f &D);
    static bool checkCollisionLC(const SMath::vec2f &s, const SMath::vec2f &e, const SMath::vec2f &c, const float &r);
    static bool checkCollisionRects(const SMath::Geometry::RectGeometry &r1, const SMath::Geometry::RectGeometry &r2);
    static void createBVH();

    void setIsDynamic(bool _d);
    void setIsTriger(bool _d);

    bool getIsDynamic() { return isDynamic; }
    bool getIsTriger() { return isTriger; }
    virtual SMath::vec2f getNormal(int i) { return 0.f; }
    std::vector<Collider *> getBVHObjects(SMath::Geometry::RectGeometry rect);
};
