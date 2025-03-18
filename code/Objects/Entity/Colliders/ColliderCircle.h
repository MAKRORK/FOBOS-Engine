#pragma once

#include "Collider.h"

class ColliderCircle : public Collider, public Circle
{
private:
    void updateCircle();

public:
    ColliderCircle(float _radius) : Collider(COLLIDER_TYPE_CIRCLE)
    {
        setRadius(_radius);
    }
    ColliderCircle(float _radius, SMath::vec2f _pos) : Collider(_pos, COLLIDER_TYPE_CIRCLE)
    {
        setRadius(_radius);
    }
    void collision() override;

    void setRadius(float _radius) override;
};