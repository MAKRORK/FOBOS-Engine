#pragma once

#include "Collider.h"

class ColliderLine : public Collider, public Line
{
public:
    ColliderLine(SMath::vec2f _p1, SMath::vec2f _p2) : Collider(COLLIDER_TYPE_LINE)
    {
        setLine(SMath::side(_p1, _p2));
    }
    ColliderLine(SMath::side _s) : Collider(COLLIDER_TYPE_LINE)
    {
        setLine(_s);
    }
    ColliderLine(SMath::vec2f _pos, SMath::vec2f _p1, SMath::vec2f _p2) : Collider(_pos, COLLIDER_TYPE_LINE)
    {
        setLine(SMath::side(_p1, _p2));
    }
    ColliderLine(SMath::vec2f _pos, SMath::side _s) : Collider(_pos, COLLIDER_TYPE_LINE)
    {
        setLine(_s);
    }

    SMath::side getLine() override;

    SMath::vec2f getPoint1() override;
    SMath::vec2f getPoint2() override;

    void collision() override {}
};