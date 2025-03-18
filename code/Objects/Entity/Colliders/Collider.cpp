#include "Collider.h"
#include "../../../Interfaces/World.h"
#include "../../../Interfaces/Render.h"
#include "ColliderPolygon.h"
#include "../Entity.h"
#include "ColliderRect.h"
#include <cmath>
#include "BVH.h"

vector<Collider *> Collider::colliders;
BVH *Collider::bvh;

void Collider::setRect(SMath::vec2f _tl, SMath::vec2f _br)
{
    rect.tl = _tl;
    rect.br = _br;
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
raycastResult Collider::raycast(SMath::vec2f s, SMath::vec2f e, Object *ignore, bool draw, Camera *cam)
{
    raycastResult result;
    SMath::vec2f nrm = (e - s);
    for (int i = 0; i < colliders.size(); i++)
    {

        Collider *col = colliders[i];
        if (ignore && ignore == col->getParent())
            continue;

        if (!checkCollisionLC(s, e, col->getCenterCircle() + col->getWorldPos(), col->getRadiusCircle()))
        {
            continue;
        }
        if (col)
        {

            if (col->getType() == COLLIDER_TYPE_RECT)
            {
                ColliderRect *rect = dynamic_cast<ColliderRect *>(col);

                collidedObject colObj;
                bool isColl = false;
                for (int i = 0; i < 4; i++)
                {
                    if (SMath::scalar(rect->getNormal(i), nrm) > 0)
                        continue;
                    collisionLinesResult res = checkLineIntersection(s, e, rect->getSide(i).p1, rect->getSide(i).p2);
                    if (res.isColliding)
                    {
                        isColl = true;
                        if (!colObj.obj)
                        {
                            colObj.obj = col->getParent();
                        }
                        colObj.points.push_back(res.point);
                    }
                }
                if (isColl)
                {
                    result.isColliding = true;
                    result.collidedObjects.push_back(colObj);
                }
            }
            else if (col->getType() == COLLIDER_TYPE_POLY)
            {
                ColliderPolygon *pol = dynamic_cast<ColliderPolygon *>(col);

                collidedObject colObj;
                bool isColl = false;
                for (int i = 0; i < pol->getSize(); i++)
                {
                    if (SMath::scalar(pol->getNormal(i), nrm) > 0)
                        continue;
                    collisionLinesResult res = checkLineIntersection(s, e, pol->getSide(i).p1, pol->getSide(i).p2);
                    if (res.isColliding)
                    {
                        isColl = true;
                        if (!colObj.obj)
                        {
                            colObj.obj = col->getParent();
                        }
                        colObj.points.push_back(res.point);
                    }
                }
                if (isColl)
                {
                    result.isColliding = true;
                    result.collidedObjects.push_back(colObj);
                }
            }
            else if (col->getType() == COLLIDER_TYPE_CIRCLE)
            {

                collisionCircleResult res = intersectLineCircle(s, e, col->getParent()->getWorldPos(), col->getRadiusCircle());
                if (res.isColliding)
                {
                    collidedObject colObj;
                    colObj.obj = col->getParent();
                    colObj.points = res.points;
                    result.isColliding = true;
                    result.collidedObjects.push_back(colObj);
                }
            }
        }
    }
    //}
    if (!cam)
    {
        cam = World::getMainCamera();
    }
    if (draw && cam)
    {
        cam->addToRender(new LineShape(SMath::side(s, e)));
        if (result.isColliding)
        {

            for (int i = 0; i < result.collidedObjects.size(); i++)
            {
                for (int j = 0; j < result.collidedObjects[i].points.size(); j++)
                {
                    cam->addToRender(new CircleShape(result.collidedObjects[i].points[j], 5.f, fv::Color::red));
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

collisionLinesResult Collider::checkLineIntersection(const SMath::vec2f &A, const SMath::vec2f &B,
                                                     const SMath::vec2f &C, const SMath::vec2f &D)
{
    float denominator = (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);
    if (denominator == 0.0f)
    {
        return {false, {0.0f, 0.0f}};
    }

    float t = ((C.x - A.x) * (D.y - C.y) - (C.y - A.y) * (D.x - C.x)) / denominator;
    float u = ((C.x - A.x) * (B.y - A.y) - (C.y - A.y) * (B.x - A.x)) / denominator;

    if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f)
    {
        SMath::vec2f intersectionPoint = {
            A.x + t * (B.x - A.x),
            A.y + t * (B.y - A.y)};
        return {true, intersectionPoint};
    }

    return {false, {0.0f, 0.0f}};
}

bool Collider::checkCollisionLC(const SMath::vec2f &s, const SMath::vec2f &e, const SMath::vec2f &c, const float &r)
{
    SMath::vec2f d = e - s;
    float t = SMath::clamp(SMath::scalar(c - s, d) / SMath::sqrLength(d), 0.f, 1.f);
    return SMath::sqrLength(s + t * d, c) <= r * r;
}

void Collider::createBVH()
{
    bvh = new BVH(colliders);
}

collisionCircleResult Collider::intersectLineCircle(const SMath::vec2f &p1, const SMath::vec2f &p2, const SMath::vec2f &center, float radius)
{
    collisionCircleResult result;
    result.isColliding = false;

    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    float a = dx * dx + dy * dy;
    float b = 2 * (dx * (p1.x - center.x) + dy * (p1.y - center.y));
    float c = (p1.x - center.x) * (p1.x - center.x) + (p1.y - center.y) * (p1.y - center.y) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return result;
    }

    discriminant = std::sqrt(discriminant);
    float t1 = (-b - discriminant) / (2 * a);
    float t2 = (-b + discriminant) / (2 * a);

    if (t1 >= 0.0f && t1 <= 1.0f)
    {
        result.points.push_back({p1.x + t1 * dx, p1.y + t1 * dy});
    }
    if (t2 >= 0.0f && t2 <= 1.0f && t1 != t2)
    {
        result.points.push_back({p1.x + t2 * dx, p1.y + t2 * dy});
    }

    result.isColliding = !result.points.empty();
    return result;
}
