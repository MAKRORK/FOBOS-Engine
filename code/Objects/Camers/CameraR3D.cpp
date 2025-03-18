#include "CameraR3D.h"
#include "../Entity/Colliders/Collider.h"
#include "../../Global.h"

void CameraR3D::render()
{
    float f = SMath::ang2rad(fov);
    float s = getWorldRot() - f / 2.f;
    // std::cout << resolution.x << " " << resolution.y;
    for (int i = 0; i < resolution.x; i++)
    {

        raycastResult res = Collider::raycast(getWorldPos(), getWorldPos() + SMath::getVectorFromAngle(s) * distance, getParent(), true, Global::miniMapCam);
        s += f / resolution.x;
    }
}
