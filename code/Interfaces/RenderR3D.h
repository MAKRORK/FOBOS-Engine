#pragma once
#include "Render.h"

class RenderR3D : public Render
{
private:
public:
    static void renderRayLine(int x, float h, int context, fv::context cont, SMath::vec2 res, SMath::vec2f size, float dist, float aspect, int texture_id);
    static void renderTrap(float x1, float x2, float h1, float h2, fv::context cont, SMath::vec2f size, int texture_id);
    static void renderSky(float angle, int texture_id, int context, fv::context cont, SMath::vec2f size);
    static void renderFloor(int context, fv::context cont, SMath::vec2f size);
    static void renderSprite(SMath::vec2 pos, int texture_id, int context, fv::context cont, SMath::vec2f size, SMath::vec2 screenSize);
};
