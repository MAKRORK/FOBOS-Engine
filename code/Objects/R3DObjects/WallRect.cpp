#include "WallRect.h"
#include "../Entity/Colliders/ColliderRect.h"

void WallRect::init(SMath::vec2f _size)
{
    size = _size;
    setSize(4);
    setPoint(0, 0.f);
    setPoint(1, SMath::vec2f(_size.x, 0.f));
    setPoint(2, _size);
    setPoint(3, SMath::vec2f(0.f, _size.y));
    Collider *col = new ColliderRect(_size);
    Shape *shp = new RectShape(_size);
    shp->setColor(fv::Color::white);
    setWallCollider(col);
    setWallShape(shp);
}

void WallRect::setRectSize(SMath::vec2f _size)
{
    init(_size);
}

SMath::vec2f WallRect::getRectSize()
{
    return size;
}
