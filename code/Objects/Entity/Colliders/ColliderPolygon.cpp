#include "ColliderPolygon.h"
#include "../../../Algoritms/GeometryAlgoritms.h"

void ColliderPolygon::recalculateNormals()
{

    for (int i = 0; i < getSize(); i++)
    {
        normals[i] = SMath::Geometry::getNormal(getRelSide(i), getCenterCircle());
    }
}

void ColliderPolygon::updateCircle()
{
    SMath::Geometry::CircleGeometry g = SMath::Geometry::findMinCircleCopy(getPoints());
    setCircleCenter(g.center);
    setCircleRad(g.radius);
    recalculateNormals();
    setInRect();
}

void ColliderPolygon::setInRect()
{
    SMath::vec2f mtl;
    SMath::vec2f mbr;
    mtl = getPoint(0);
    mbr = getPoint(0);
    for (int i = 1; i < getSize(); i++)
    {
        mtl.x = min(getPoint(i).x, mtl.x);
        mtl.y = min(getPoint(i).y, mtl.y);
        mbr.x = max(getPoint(i).x, mbr.x);
        mbr.y = max(getPoint(i).y, mbr.y);
    }
    setRect(mtl, mbr);
}

SMath::side ColliderPolygon::getSide(int i)
{
    SMath::side s;
    s = SMath::side(getPoint(i), getPoint((i + 1) % getSize()));
    if (getParent())
    {
        return s + getParent()->getWorldPos();
    }
    else
        return s;
}

SMath::side ColliderPolygon::getRelSide(int i)
{
    return SMath::side(getPoint(i), getPoint((i + 1) % getSize()));
}

vector<SMath::side> ColliderPolygon::getSides()
{
    vector<SMath::side> ss;
    for (int i = 0; i < getSize(); i++)
    {
        ss.push_back(getSide(i));
    }
    return ss;
}

SMath::vec2f ColliderPolygon::getNormal(int i)
{
    return normals[i];
}
