#include "Camera2D.h"
#include "../../Interfaces/Render.h"

void Camera2D::render()
{
    // Render::clearContext(getRenderContext());
    fv::renderContext cont = fv::renderContext(getRenderContext(), fv::context((getOffset() - (getWorldPos() - (getSize() / 2))), getOffsetScale()));
    Render::renderAllShapes(cont);
    Render::renderShapes(shapes, cont);
    Render::renderContext(getScreenPos(), getRenderContext());
    clearBuffer();
}

void Camera2D::renderBuffer()
{
    fv::renderContext cont = fv::renderContext(getRenderContext(), fv::context((getOffset() - (getWorldPos() - (getSize() / 2))), getOffsetScale()));
    Render::renderShapes(shapes, cont);
    clearBuffer();
}
