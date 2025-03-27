#pragma once
#include "Collider.h"
#include "../../../Primitives/Primitives2D.h"

class ColliderPolygon : public Collider, public Polygon
{
private:
    std::vector<SMath::vec2f> normals;
    void recalculateNormals();
    void updateCircle();
    void setInRect();

public:
    ColliderPolygon() : Collider(COLLIDER_TYPE_POLY) {}
    ColliderPolygon(int _size) : Collider(COLLIDER_TYPE_POLY)
    {
        setSize(_size);
        normals.resize(_size);
    }
    ColliderPolygon(SMath::vec2f _pos) : Collider(_pos, COLLIDER_TYPE_POLY) {}

    void setSize(int _size) override
    {
        Polygon::setSize(_size);
        normals.resize(_size);
    }
    void setPoint(int id, SMath::vec2f p) override
    {
        Polygon::setPoint(id, p);
        updateCircle();
    }

    SMath::side getSide(int i);
    SMath::side getRelSide(int i);
    vector<SMath::side> getSides();
    SMath::vec2f getNormal(int i) override;

    void collision() override {}
};