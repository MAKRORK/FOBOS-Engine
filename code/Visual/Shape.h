#pragma once
#include "../Interfaces/SMath.h"
#include "../Objects/Object.h"
#include "VisualStructs.h"

#define SHAPE_TYPE_CIRCLE 0
#define SHAPE_TYPE_RECT 1
#define SHAPE_TYPE_LINE 2
#define SHAPE_TYPE_POLY 3

class Shape : public Object
{
private:
    int type = -1;
    fv::Color color = fv::Color();
    fv::context context = fv::context();

public:
    Shape(int _type) : Object() { type = _type; }
    Shape(SMath::vec2f _pos, int _type) : Object(_pos) { type = _type; }
    Shape(int _type, fv::Color _color) : Object()
    {
        type = _type;
        color = _color;
    }
    Shape(SMath::vec2f _pos, int _type, fv::Color _color) : Object(_pos)
    {
        type = _type;
        color = _color;
    }
    int getType() { return type; }

    fv::context getContext() { return context; }

    void setContext(fv::context _cont) { context = _cont; }

    fv::Color getColor() { return color; }

    void setColor(fv::Color _c) { color = _c; }

    virtual void draw(fv::renderContext c = fv::renderContext()) {}
};

class Circle : public Shape
{
private:
    float radius;

public:
    Circle() : Shape(SHAPE_TYPE_CIRCLE) { radius = 10.f; }
    Circle(SMath::vec2f _pos) : Shape(_pos, SHAPE_TYPE_CIRCLE) { radius = 10.f; }
    Circle(float _r) : Shape(SHAPE_TYPE_CIRCLE) { radius = _r; }
    Circle(SMath::vec2f _pos, float _r) : Shape(_pos, SHAPE_TYPE_CIRCLE) { radius = _r; }
    Circle(fv::Color _c) : Shape(SHAPE_TYPE_CIRCLE, _c) { radius = 10.f; }
    Circle(SMath::vec2f _pos, fv::Color _c) : Shape(_pos, SHAPE_TYPE_CIRCLE, _c) { radius = 10.f; }
    Circle(float _r, fv::Color _c) : Shape(SHAPE_TYPE_CIRCLE, _c) { radius = _r; }
    Circle(SMath::vec2f _pos, float _r, fv::Color _c) : Shape(_pos, SHAPE_TYPE_CIRCLE, _c) { radius = _r; }

    void draw(fv::renderContext c = fv::renderContext()) override;

    void setRadius(float _r) { radius = _r; }

    float getRadius() { return radius; }
    float getScaleRadius() { return radius * getWorldScale(); }
};

class Rect : public Shape
{
private:
    SMath::vec2f size;

public:
    Rect() : Shape(SHAPE_TYPE_RECT) {}
    Rect(SMath::vec2f _s) : Shape(SHAPE_TYPE_RECT) { size = _s; }
    Rect(SMath::vec2f _pos, SMath::vec2f _s) : Shape(_pos, SHAPE_TYPE_RECT) { size = _s; }

    void draw(fv::renderContext c = fv::renderContext()) override;

    SMath::vec2f getSize() { return size; }
    SMath::vec2f getScaleSize() { return size * getWorldScale(); }

    void setSize(SMath::vec2f _s) { size = _s; }
};

class Line : public Shape
{
private:
    SMath::side line;

public:
    Line() : Shape(SHAPE_TYPE_LINE) {}
    Line(SMath::side _line) : Shape(SHAPE_TYPE_LINE) { line = _line; }
    Line(SMath::vec2f _pos, SMath::side _line) : Shape(_pos, SHAPE_TYPE_LINE) { line = _line; }

    void draw(fv::renderContext c = fv::renderContext()) override;

    SMath::side getLine() { return line; }
    SMath::side getScaleLine();

    void setLine(SMath::side _line) { line = _line; }

    SMath::vec2f getPoint1() { return line.p1; }
    SMath::vec2f getPoint2() { return line.p2; }

    void setPoint1(SMath::vec2f p) { line.p1 = p; }
    void setPoint2(SMath::vec2f p) { line.p2 = p; }
};
