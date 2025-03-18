#pragma once
#include <iostream>

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
    float scalar(SMath::vec2f a, SMath::vec2f b);
    float pov(float a, int p);
    side scaledSide(side s, float sc);
    vec2f getVectorFromAngle(float a);
    float ang2rad(float a);
    float rad2ang(float r);
    const float pi = 3.1415926;
    float sqrLength(SMath::vec2f p);
    float sqrLength(SMath::vec2f p1, SMath::vec2f p2);
    float clamp(float a, float mn, float mx);
}

std::ostream &operator<<(std::ostream &os, const SMath::vec2f &p);
