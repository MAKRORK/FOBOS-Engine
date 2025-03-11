#pragma once

#include "../Interfaces/SMath.h"

#define uint8 char

namespace fv
{
    struct Color
    {
        uint8 r, g, b, a;

        Color();
        Color(uint8 _r, uint8 _g, uint8 _b);
        Color(uint8 _r, uint8 _g, uint8 _b, uint8 _a);

        static Color red;
        static Color green;
        static Color blue;
        static Color yellow;
        static Color magenta;
        static Color cyan;
        static Color black;
        static Color white;
    };
    struct context
    {
        context();
        context(SMath::vec2f _offset, float _scale);

        SMath::vec2f offset;
        float scale;
    };

    struct renderContext
    {
        int context = 0;
        fv::context offContext = fv::context();
        renderContext() {}
        renderContext(int _c) : context(_c) {}
        renderContext(int _c, fv::context _oc) : context(_c), offContext(_oc) {}
    };

};