#include "Camera.h"
#include "../../Interfaces/Render.h"
#include <iostream>

void Camera::clearBuffer()
{
    for (Shape *s : shapes)
    {
        delete s;
    }
    shapes.clear();
}

void Camera::NewRenderContext(fv::Color col)
{
    backgroundColor = col;
    context.context = Render::createNewContext(size, backgroundColor);
}

void Camera::setSize(SMath::vec2 _size)
{
    size = _size;
    Render::resizeContext(size, context.context);
}

void Camera::addToRender(Shape *s)
{
    shapes.push_back(s);
}

void Camera::setBackgroundColor(fv::Color col)
{
    backgroundColor = col;
    Render::changeClearColorContext(col, context.context);
}
