#pragma once
#include "../Object.h"
#include "../../Interfaces/SMath.h"

class Block : public Object
{
private:
public:
    Block() : Object() {}
    Block(SMath::vec2f _pos) : Object(_pos) {}
};
