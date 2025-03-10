#include "Shape.h"
#include "../Interfaces/Render.h"

void Circle::draw()
{
    Render::render(this, getContext());
}

void Rect::draw()
{
    Render::render(this, getContext());
}
