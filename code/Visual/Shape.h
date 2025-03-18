#pragma once
#include "../Interfaces/SMath.h"
#include "../Objects/Object.h"
#include "VisualStructs.h"
#include "../Primitives/Primitives2D.h"

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

class CircleShape : public Shape, public Circle
{
public:
    CircleShape() : Shape(SHAPE_TYPE_CIRCLE) { setRadius(10.f); }
    CircleShape(SMath::vec2f _pos) : Shape(_pos, SHAPE_TYPE_CIRCLE) { setRadius(10.f); }
    CircleShape(float _r) : Shape(SHAPE_TYPE_CIRCLE) { setRadius(_r); }
    CircleShape(SMath::vec2f _pos, float _r) : Shape(_pos, SHAPE_TYPE_CIRCLE) { setRadius(_r); }
    CircleShape(fv::Color _c) : Shape(SHAPE_TYPE_CIRCLE, _c) { setRadius(10.f); }
    CircleShape(SMath::vec2f _pos, fv::Color _c) : Shape(_pos, SHAPE_TYPE_CIRCLE, _c) { setRadius(10.f); }
    CircleShape(float _r, fv::Color _c) : Shape(SHAPE_TYPE_CIRCLE, _c) { setRadius(_r); }
    CircleShape(SMath::vec2f _pos, float _r, fv::Color _c) : Shape(_pos, SHAPE_TYPE_CIRCLE, _c) { setRadius(_r); }

    void draw(fv::renderContext c = fv::renderContext()) override;

    float getScaleRadius() { return getRadius() * getWorldScale(); }
};

class RectShape : public Shape, public Rect
{

public:
    RectShape() : Shape(SHAPE_TYPE_RECT) {}
    RectShape(SMath::vec2f _s) : Shape(SHAPE_TYPE_RECT) { setSize(_s); }
    RectShape(SMath::vec2f _pos, SMath::vec2f _s) : Shape(_pos, SHAPE_TYPE_RECT) { setSize(_s); }

    void draw(fv::renderContext c = fv::renderContext()) override;

    SMath::vec2f getScaleSize() { return getSize() * getWorldScale(); }
};

class LineShape : public Shape, public Line
{
public:
    LineShape() : Shape(SHAPE_TYPE_LINE) {}
    LineShape(SMath::side _line) : Shape(SHAPE_TYPE_LINE) { setLine(_line); }
    LineShape(SMath::side _line, fv::Color _c) : Shape(SHAPE_TYPE_LINE)
    {
        setLine(_line);
        setColor(_c);
    }
    LineShape(SMath::vec2f _pos, SMath::side _line) : Shape(_pos, SHAPE_TYPE_LINE) { setLine(_line); }

    void draw(fv::renderContext c = fv::renderContext()) override;

    SMath::side getScaleLine();
};

class PolygonShape : public Shape, public Polygon
{

public:
    PolygonShape() : Shape(SHAPE_TYPE_POLY) {}
    PolygonShape(int _size) : Shape(SHAPE_TYPE_POLY) { setSize(_size); }
    PolygonShape(SMath::vec2f _pos) : Shape(_pos, SHAPE_TYPE_POLY) {}

    SMath::vec2f getScaledPoint(int id);

    void draw(fv::renderContext c = fv::renderContext()) override;
};
