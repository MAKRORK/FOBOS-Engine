#pragma once

#include "../Object.h"
#include "../../Visual/Shape.h"
#include <vector>

class Camera : public Object
{
private:
    SMath::vec2 size = 0.f;
    SMath::vec2f screenPos = 0.f;
    fv::renderContext context = fv::renderContext(0, fv::context(0.f, 1.f));
    fv::Color backgroundColor = fv::Color::cyan;

protected:
    std::vector<Shape *> shapes;
    void clearBuffer();

public:
    Camera() : Object() {}
    Camera(SMath::vec2 _size) : Object() { size = _size; }
    Camera(SMath::vec2f _pos, SMath::vec2 _size) : Object(_pos) { size = _size; }

    void NewRenderContext(fv::Color col = fv::Color::black);

    void setContext(fv::context c) { context.offContext = c; }
    void setScale(float s) { context.offContext.scale = s; }
    void setOffset(SMath::vec2f o) { context.offContext.offset = o; }
    void setScreenPos(SMath::vec2f p) { screenPos = p; }

    fv::context getContext() { return context.offContext; }
    float getOffsetScale() { return context.offContext.scale; }
    SMath::vec2f getOffset() { return context.offContext.offset; }
    SMath::vec2f getScreenPos() { return screenPos; }

    void setSize(SMath::vec2 _size);

    SMath::vec2 getSize() { return size; }

    fv::renderContext getFullRenderContext() { return context; }

    int getRenderContext() { return context.context; }

    void addToRender(Shape *s);

    void setBackgroundColor(fv::Color col);

    fv::Color getBackgroundColor() { return backgroundColor; }

    virtual void render() {}
};
