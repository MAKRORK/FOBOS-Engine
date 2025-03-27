#pragma once
#include "Render.h"

class RenderR3D : public Render
{
private:
public:
    static void renderRayLine(int x, float h, int context, fv::context cont, SMath::vec2 res, SMath::vec2f size, float dist, float aspect, int texture_id);
    static void renderTrap(float x1, float x2, float h1, float h2, fv::context cont, SMath::vec2f size, int texture_id);
};
