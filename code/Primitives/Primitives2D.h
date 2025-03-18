#pragma once
#include "../Interfaces/SMath.h"
#include <vector>
#include <iostream>

class Circle
{
private:
    float radius;

public:
    virtual void setRadius(float _r) { radius = _r; }

    virtual float getRadius() { return radius; }
};

class Rect
{
private:
    SMath::vec2f size;

public:
    SMath::vec2f getSize() { return size; }

    virtual void setSize(SMath::vec2f _s) { size = _s; }
};

class Line
{
private:
    SMath::side line;

public:
    virtual SMath::side getLine() { return line; }

    void setLine(SMath::side _line) { line = _line; }

    virtual SMath::vec2f getPoint1() { return line.p1; }
    virtual SMath::vec2f getPoint2() { return line.p2; }

    void setPoint1(SMath::vec2f p) { line.p1 = p; }
    void setPoint2(SMath::vec2f p) { line.p2 = p; }
};

class Polygon
{
private:
    std::vector<SMath::vec2f> points;

public:
    virtual void setSize(int _size) { points.resize(_size); }
    virtual void setPoint(int id, SMath::vec2f p) { points[id] = p; }

    int getSize() { return points.size(); }
    SMath::vec2f getPoint(int id) { return points[id]; }

    std::vector<SMath::vec2f> getPoints() { return points; }
};