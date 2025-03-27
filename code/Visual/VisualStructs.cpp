#include "VisualStructs.h"

fv::Color fv::Color::red = Color(255, 0, 0);
fv::Color fv::Color::green = Color(0, 255, 0);
fv::Color fv::Color::blue = Color(0, 0, 255);
fv::Color fv::Color::yellow = Color(255, 255, 0);
fv::Color fv::Color::magenta = Color(255, 0, 255);
fv::Color fv::Color::cyan = Color(0, 255, 255);
fv::Color fv::Color::black = Color(0, 0, 0);
fv::Color fv::Color::white = Color(255, 255, 255);

fv::Color::Color()
{
    r = 0;
    g = 0;
    b = 0;
    a = 255;
}

fv::Color::Color(uint8 _c)
{
    r = _c;
    g = _c;
    b = _c;
    a = 255;
}

fv::Color::Color(uint8 _r, uint8 _g, uint8 _b)
{
    r = _r;
    g = _g;
    b = _b;
    a = 255;
}

fv::Color::Color(uint8 _r, uint8 _g, uint8 _b, uint8 _a)
{
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}

fv::context::context()
{
    offset = SMath::vec2f(0.f, 0.f);
    scale = 1.f;
}

fv::context::context(SMath::vec2f _offset, float _scale)
{
    offset = _offset;
    scale = _scale;
}
