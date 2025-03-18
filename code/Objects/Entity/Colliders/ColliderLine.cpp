#include "ColliderLine.h"

SMath::side ColliderLine::getLine()
{
    if (getParent())
    {
        return Line::getLine() + getParent()->getWorldPos();
    }
    return Line::getLine();
}
SMath::vec2f ColliderLine::getPoint1()
{
    if (getParent())
    {
        return Line::getLine().p1 + getParent()->getWorldPos();
    }
    return Line::getLine().p1;
}
SMath::vec2f ColliderLine::getPoint2()
{
    if (getParent())
    {
        return Line::getLine().p2 + getParent()->getWorldPos();
    }
    return Line::getLine().p1;
}