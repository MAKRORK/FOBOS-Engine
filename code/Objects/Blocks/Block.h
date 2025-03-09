#pragma once
#include "../Object.h"

class Block : public Object
{
private:
public:
    void render();
    Block() : Object() {}
    Block(sf::Vector2f _pos) : Object(_pos) {}
};
