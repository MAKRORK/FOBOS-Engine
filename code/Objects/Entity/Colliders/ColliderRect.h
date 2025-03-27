#pragma once

#include "Collider.h"
#include "../../../Primitives/Primitives2D.h"

class ColliderRect : public Collider, public Rect
{
private:
    SMath::side sides[4] = {SMath::side(), SMath::side(), SMath::side(), SMath::side()};
    void init();

    void updateCircle();

public:
    ColliderRect(SMath::vec2f _size) : Collider(COLLIDER_TYPE_RECT)
    {
        setSize(_size);
    }
    ColliderRect(SMath::vec2f _pos, SMath::vec2f _size) : Collider(_pos, COLLIDER_TYPE_RECT)
    {
        setSize(_size);
    }
    void collision() override;

    void setSize(SMath::vec2f _size)
    {
        Rect::setSize(_size);
        init();
    }

    SMath::side getSide(int i);
    vector<SMath::side> getSides();
    SMath::vec2f getNormal(int i) override;
};