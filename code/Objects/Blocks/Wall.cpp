#include "Wall.h"
#include <iostream>
#include "../Entity/Colliders/Collider.h"
#include "../../Interfaces/ForSFML.h"
#include "../../Visual/Shape.h"
#include "../Entity/Colliders/ColliderRect.h"

void Wall::init()
{
    addChildren(new ColliderRect(SMath::vec2f(32.f, 32.f)));
}
