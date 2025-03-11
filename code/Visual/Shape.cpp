#include "Shape.h"
#include "../Interfaces/Render.h"

void Circle::draw(fv::renderContext c)
{

    Render::render(this, fv::context(getContext().offset + c.offContext.offset, getContext().scale * c.offContext.scale), c.context);
}

void Rect::draw(fv::renderContext c)
{
    Render::render(this, fv::context(getContext().offset + c.offContext.offset, getContext().scale * c.offContext.scale), c.context);
}

void Line::draw(fv::renderContext c)
{
    Render::render(this, fv::context(getContext().offset + c.offContext.offset, getContext().scale * c.offContext.scale), c.context);
}

SMath::side Line::getScaleLine()
{
    return SMath::scaledSide(line, getWorldScale());
}
