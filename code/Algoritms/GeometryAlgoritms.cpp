#include "GeometryAlgoritms.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

double dist(const SMath::vec2f &a, const SMath::vec2f &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

SMath::Geometry::CircleGeometry SMath::Geometry::circleFromTwoPoints(const SMath::vec2f &p1, const SMath::vec2f &p2)
{
    SMath::vec2f center = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    double radius = dist(p1, p2) / 2;
    return {center, radius};
}

SMath::Geometry::CircleGeometry circleFromThreePoints(const SMath::vec2f &p1, const SMath::vec2f &p2, const SMath::vec2f &p3)
{
    double ax = p1.x, ay = p1.y;
    double bx = p2.x, by = p2.y;
    double cx = p3.x, cy = p3.y;

    double d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
    double ux = ((ax * ax + ay * ay) * (by - cy) + (bx * bx + by * by) * (cy - ay) + (cx * cx + cy * cy) * (ay - by)) / d;
    double uy = ((ax * ax + ay * ay) * (cx - bx) + (bx * bx + by * by) * (ax - cx) + (cx * cx + cy * cy) * (bx - ax)) / d;

    SMath::vec2f center = {(float)ux, (float)uy};
    double radius = dist(center, p1);

    return {center, radius};
}

bool isInside(const SMath::Geometry::CircleGeometry &c, const SMath::vec2f &p)
{
    return dist(c.center, p) <= c.radius + 1e-9;
}

SMath::Geometry::CircleGeometry SMath::Geometry::trivialCircle(const vector<SMath::vec2f> &R)
{
    if (R.empty())
        return {{0, 0}, 0};
    if (R.size() == 1)
        return {R[0], 0};
    if (R.size() == 2)
        return circleFromTwoPoints(R[0], R[1]);
    return circleFromThreePoints(R[0], R[1], R[2]);
}

SMath::Geometry::CircleGeometry SMath::Geometry::welzl(vector<SMath::vec2f> &P, vector<SMath::vec2f> R, int n)
{
    if (n == 0 || R.size() == 3)
    {
        return trivialCircle(R);
    }

    int idx = rand() % n;
    SMath::vec2f p = P[idx];

    swap(P[idx], P[n - 1]);

    SMath::Geometry::CircleGeometry d = welzl(P, R, n - 1);

    if (isInside(d, p))
    {
        return d;
    }

    R.push_back(p);
    return welzl(P, R, n - 1);
}

SMath::Geometry::CircleGeometry SMath::Geometry::findMinCircle(vector<SMath::vec2f> &points)
{
    srand(time(0));
    random_shuffle(points.begin(), points.end());
    return welzl(points, {}, points.size());
}

SMath::Geometry::CircleGeometry SMath::Geometry::findMinCircleCopy(vector<SMath::vec2f> points)
{
    std::vector<SMath::vec2f> vec(points);
    return findMinCircle(vec);
}

SMath::vec2f SMath::Geometry::getCross(SMath::vec2f p)
{
    return SMath::vec2f(p.y, -p.x);
}

SMath::vec2f SMath::Geometry::getNormal(SMath::vec2f p1, SMath::vec2f p2, SMath::vec2f c)
{
    vec2f h = (p1 + p2) / 2.f;
    vec2f tc = c - h;
    vec2f cr = normalize(getCross(p2 - p1));
    if (scalar(cr, tc) < 0)
    {
        return cr;
    }

    return -cr;
}

SMath::vec2f SMath::Geometry::getNormal(side s, SMath::vec2f c)
{
    return getNormal(s.p1, s.p2, c);
}
