#pragma once
#include <iostream>
#include <cmath>

#define FAC_3 1.f / 6.f
#define FAC_5 1.f / 120.f
#define FAC_7 1.f / 5040.f
#define FAC_9 1.f / 362880.f
#define FAC_11 1.f / 39916800.f

namespace SMath
{
    struct vec2
    {
        int x;
        int y;
        vec2() : x(0), y(0) {}
        vec2(int _x, int _y) : x(_x), y(_y) {}
        vec2(int _p) : x(_p), y(_p) {}

        vec2 operator+(const vec2 &b) const { return vec2(x + b.x, y + b.y); }
        vec2 &operator+=(const vec2 &b)
        {
            x += b.x;
            y += b.y;
            return *this;
        }
        vec2 operator-(const vec2 &b) const { return vec2(x - b.x, y - b.y); }
        vec2 operator+(int b) const { return vec2(x + b, y + b); }
        vec2 operator-(int b) const { return vec2(x - b, y - b); }
        vec2 operator*(int b) const { return vec2(x * b, y * b); }
        vec2 operator/(int b) const { return vec2(x / b, y / b); }
        vec2 operator-() const { return vec2(-x, -y); }
    };
    struct vec2f
    {
        float x;
        float y;
        vec2f() : x(0.f), y(0.f) {}
        vec2f(float _x, float _y) : x(_x), y(_y) {}
        vec2f(float _p) : x(_p), y(_p) {}
        vec2f(vec2 v) : x(v.x), y(v.y) {}

        vec2f operator+(const vec2f &b) const { return vec2f(x + b.x, y + b.y); }
        vec2f &operator+=(const vec2f &b)
        {
            x += b.x;
            y += b.y;
            return *this;
        }
        vec2f &operator-=(const vec2f &b)
        {
            x -= b.x;
            y -= b.y;
            return *this;
        }
        vec2f &operator*=(const vec2f &b)
        {
            x *= b.x;
            y *= b.y;
            return *this;
        }
        vec2f &operator/=(const vec2f &b)
        {
            x /= b.x;
            y /= b.y;
            return *this;
        }
        vec2f operator-(const vec2f &b) const { return vec2f(x - b.x, y - b.y); }
        vec2f operator+(float b) const { return vec2f(x + b, y + b); }
        vec2f operator-(float b) const { return vec2f(x - b, y - b); }
        vec2f operator*(float b) const { return vec2f(x * b, y * b); }
        vec2f operator/(float b) const { return vec2f(x / b, y / b); }
        vec2f operator-() const { return vec2f(-x, -y); }
    };

    vec2f operator*(float a, const vec2f &v);

    struct side
    {
        SMath::vec2f p1;
        SMath::vec2f p2;
        side() : p1(SMath::vec2f(0, 0)), p2(SMath::vec2f(0, 0)) {}
        side(SMath::vec2f _p1, SMath::vec2f _p2) : p1(_p1), p2(_p2) {}
        side operator+(SMath::vec2f v)
        {
            return side{p1 + v, p2 + v};
        }
    };
    // typedef vec2fs vec2f;
    SMath::vec2f normalize(SMath::vec2f vec);
    float distToLine(SMath::vec2f p1, SMath::vec2f p2, SMath::vec2f p);
    float length(SMath::vec2f p1, SMath::vec2f p2);
    float distToLine(side s, SMath::vec2f p);
    float length(side s);
    float length(SMath::vec2f p);
    inline float scalar(SMath::vec2f a, SMath::vec2f b) { return a.x * b.x + a.y * b.y; }
    float pov(float a, int p);
    side scaledSide(side s, float sc);
    vec2f getVectorFromAngle(float a);
    float deg2rad(float a);
    float rad2deg(float r);
    const float pi = 3.14159265358979323846;
    float sqrLength(SMath::vec2f p);
    float sqrLength(SMath::vec2f p1, SMath::vec2f p2);
    float clamp(float a, float mn, float mx);
    int clamp(int a, int mn, int mx);
    float getAngleFromVector(SMath::vec2f v);
    float correctAngle(float angle);

    inline float fastSqrt(float a)
    {

        long i;
        float x2, y;
        const float threehalfs = 1.5F;

        x2 = a * 0.5F;
        y = a;
        i = *(long *)&y;
        i = 0x5f3759df - (i >> 1);
        y = *(float *)&i;
        y = y * (threehalfs - (x2 * y * y));

        return 1 / y;
    }
    inline float fast_sin(float x)
    {
        x = fmodf(x, 2 * pi);
        if (x > pi)
            x -= 2 * pi;
        if (x < -pi)
            x += 2 * pi;

        float x2 = x * x;
        float x4 = x2 * x2;
        float x8 = x4 * x4;
        return x - (x2 * x * FAC_3) + (x4 * x * FAC_5) - (x4 * x2 * x * FAC_7) + (x8 * x * FAC_9) - (x8 * x2 * x * FAC_11);
    }

    inline float fast_cos(float x)
    {
        return fast_sin(x + 1.57079632f);
    }
}

std::ostream &operator<<(std::ostream &os, const SMath::vec2f &p);
