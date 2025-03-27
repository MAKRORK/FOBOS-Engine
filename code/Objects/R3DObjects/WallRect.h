#pragma once
#include "Wall.h"

class WallRect : public Wall
{
private:
    void init(SMath::vec2f _size);
    SMath::vec2f size;

public:
    WallRect() : Wall() {}
    WallRect(SMath::vec2f _pos) : Wall(_pos) {}
    WallRect(SMath::vec2f _pos, SMath::vec2f _size) : Wall(_pos) { init(_size); }

    void setRectSize(SMath::vec2f _size);
    SMath::vec2f getRectSize();
};
