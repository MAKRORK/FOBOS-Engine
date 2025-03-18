#include "Shape.h"
#include "../Interfaces/Render.h"

void CircleShape::draw(fv::renderContext c)
{

    Render::render(this, fv::context(getContext().offset + c.offContext.offset, getContext().scale * c.offContext.scale), c.context);
}

void RectShape::draw(fv::renderContext c)
{
    Render::render(this, fv::context(getContext().offset + c.offContext.offset, getContext().scale * c.offContext.scale), c.context);
}

void LineShape::draw(fv::renderContext c)
{
    Render::render(this, fv::context(getContext().offset + c.offContext.offset, getContext().scale * c.offContext.scale), c.context);
}

SMath::side LineShape::getScaleLine()
{
    return SMath::scaledSide(getLine(), getWorldScale());
}

SMath::vec2f PolygonShape::getScaledPoint(int id)
{
    return getPoint(id) * getWorldScale();
}

void PolygonShape::draw(fv::renderContext c)
{
    // std::cout << "haha\n";
    Render::render(this, fv::context(getContext().offset + c.offContext.offset, getContext().scale * c.offContext.scale), c.context);
}
