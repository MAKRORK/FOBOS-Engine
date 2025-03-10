
#pragma once
#include "Block.h"
#include "../../Interfaces/SMath.h"
#include <iostream>

class Wall : public Block
{
private:
    void init();

public:
    Wall() : Block() { init(); }
    Wall(SMath::vec2f _pos) : Block(_pos)
    {
        init();
    }
};
