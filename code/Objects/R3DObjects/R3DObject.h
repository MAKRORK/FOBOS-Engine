#pragma once
#include "../Object.h"
#include "../../Interfaces/SMath.h"

class R3DObject : public Object
{
private:
public:
    R3DObject() : Object() {}
    R3DObject(SMath::vec2f _pos) : Object(_pos) {}
};
