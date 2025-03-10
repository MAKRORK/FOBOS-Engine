#include "Wall.h"
#include <iostream>
#include "../Entity/Collider.h"
#include "../../Interfaces/ForSFML.h"
#include "../../Visual/Shape.h"

void Wall::init()
{
    addChildren(new ColliderRect(SMath::vec2f(32.f, 32.f)));
}
