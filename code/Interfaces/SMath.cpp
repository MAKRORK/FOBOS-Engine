#include "SMath.h"
#include <cmath>

SMath::vec2f SMath::operator*(float a, const vec2f &v)
{
    return v * a;
}

SMath::vec2f SMath::normalize(SMath::vec2f vec)
{
    if (vec.x == 0 && vec.y == 0)
    {
        return vec;
    }
    float length = sqrt(vec.x * vec.x + vec.y * vec.y);
    return SMath::vec2f(vec.x / length, vec.y / length);
}

float SMath::length(SMath::vec2f p1, SMath::vec2f p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
float SMath::length(side s)
{
    return SMath::length(s.p1, s.p2);
}
float SMath::length(SMath::vec2f p)
{
    return sqrt(p.x * p.x + p.y * p.y);
}
float SMath::scalar(SMath::vec2f a, SMath::vec2f b)
{

    return a.x * b.x + a.y * b.y;
}
float SMath::pov(float a, int p)
{
    float ans = a;
    for (int i = 1; i < p; i++)
    {
        ans *= a;
    }
    return ans;
}
SMath::side SMath::scaledSide(side s, float sc)
{
    return side(s.p1 * sc, s.p2 * sc);
}
SMath::vec2f SMath::getVectorFromAngle(float a)
{
    return SMath::vec2f(cosf(a), sinf(a));
}
float SMath::deg2rad(float a)
{
    return a / 180.f * pi;
}
float SMath::rad2deg(float r)
{
    return r * 180.f / pi;
}
float SMath::sqrLength(SMath::vec2f p)
{
    return p.x * p.x + p.y * p.y;
}
float SMath::sqrLength(SMath::vec2f p1, SMath::vec2f p2)
{
    return sqrLength(p2 - p1);
}
float SMath::clamp(float a, float mn, float mx)
{
    if (a < mn)
        return mn;
    if (a > mx)
        return mx;
    return a;
}
int SMath::clamp(int a, int mn, int mx)
{
    if (a < mn)
        return mn;
    if (a > mx)
        return mx;
    return a;
}
float SMath::getAngleFromVector(SMath::vec2f v)
{
    return atan2(v.y, v.x);
}
float SMath::correctAngle(float angle)
{
    float tau = 2 * pi;

    while (angle > tau)
    {
        angle -= tau;
    }

    while (angle < 0.f)
    {
        angle += tau;
    }
    return angle;
}
float SMath::distToLine(SMath::vec2f p1, SMath::vec2f p2, SMath::vec2f p)
{
    float a = SMath::length(p1, p);
    float b = SMath::length(p2, p);
    float c = SMath::length(p1, p2);
    float p_ = (a + b + c) / 2;
    float S = sqrt(p_ * (p_ - a) * (p_ - b) * (p_ - c));
    return 2 * S / c;
}
float SMath::distToLine(side s, SMath::vec2f p)
{
    return SMath::distToLine(s.p1, s.p2, p);
}

std::ostream &operator<<(std::ostream &os, const SMath::vec2f &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
