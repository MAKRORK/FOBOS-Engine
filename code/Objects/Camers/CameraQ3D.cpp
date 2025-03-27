#include "CameraQ3D.h"
#include "../Entity/Colliders/Collider.h"
#include "../../Global.h"
#include <cmath>
#include "../../Interfaces/RenderR3D.h"

#include <algorithm>

void CameraQ3D::render()
{
    float f = SMath::deg2rad(getFov());
    float s = getWorldRot() - f / 2.f;
    SMath::vec2f end = getWorldPos() + SMath::getVectorFromAngle(s) * getDistance();
    raycastResult res = Collider::raycast(getWorldPos(), end, getParent(), true, Global::miniMapCam);
    SMath::vec2f end1 = getWorldPos() + SMath::getVectorFromAngle(s + f) * getDistance();
    raycastResult res1 = Collider::raycast(getWorldPos(), end1, getParent(), true, Global::miniMapCam);
    vector<sideWall> result = Wall::getSidesInFov(getWorldPos(), getDistance(), getFov(), getWorldRot());
    SMath::vec2f wp = getWorldPos();
    float a = getWorldRot();
    std::sort(result.begin(), result.end(), [wp](sideWall a, sideWall b)
              {
        float ma = min(SMath::length(a.wall->getSide(a.side_id).p1 -wp), SMath::length(a.wall->getSide(a.side_id).p2 - wp));
        float mb = min(SMath::length(b.wall->getSide(b.side_id).p1 - wp), SMath::length(b.wall->getSide(b.side_id).p2 - wp));
        return ma > mb; });
    // cout << SMath::rad2deg(SMath::getAngleFromVector(end - getWorldPos())) << "\n";
    float startAng = SMath::getAngleFromVector(end - wp);
    for (sideWall sw : result)
    {
        float dist1 = SMath::length(sw.wall->getSide(sw.side_id).p1 - wp);
        float h1 = (50.f * getSize().y) / dist1;
        // // float a1 = SMath::getAngleFromVector(sw.wall->getSide(sw.side_id).p1 - wp);
        // float sc1 = SMath::scalar(SMath::normalize(end - wp), SMath::normalize(sw.wall->getSide(sw.side_id).p1 - wp));
        // float a1 = std::acos(std::clamp(sc1, -1.0f, 1.0f));
        // float x1 = (a1 / f) * getSize().x;
        // if (SMath::scalar(SMath::normalize(end1 - wp), SMath::normalize(sw.wall->getSide(sw.side_id).p1 - wp)) < SMath::scalar(SMath::normalize(end1 - wp), SMath::normalize(end - wp)))
        // {
        //     x1 = -x1;
        // }
        float dist2 = SMath::length(sw.wall->getSide(sw.side_id).p2 - wp);
        float h2 = (50.f * getSize().y) / dist2;
        // float a2 = SMath::getAngleFromVector(sw.wall->getSide(sw.side_id).p2 - wp);
        // float sc2 = SMath::scalar(SMath::normalize(end - wp), SMath::normalize(sw.wall->getSide(sw.side_id).p2 - wp));
        // float a2 = std::acos(std::clamp(sc2, -1.0f, 1.0f));
        // float x2 = (a2 / f) * getSize().x;
        // if (SMath::scalar(SMath::normalize(end1 - wp), SMath::normalize(sw.wall->getSide(sw.side_id).p2 - wp)) < SMath::scalar(SMath::normalize(end1 - wp), SMath::normalize(end - wp)))
        // {
        //     x2 = -x2;
        // }
        float dx1 = sw.wall->getSide(sw.side_id).p1.x - wp.x;
        float dy1 = sw.wall->getSide(sw.side_id).p1.y - wp.y;
        float xx1 = dx1 * cos(-a) - dy1 * sin(-a);
        float yy1 = dx1 * sin(-a) + dy1 * cos(-a);
        float x1 = getSize().x / 2.f + (yy1 / xx1) * getSize().x;

        float dx2 = sw.wall->getSide(sw.side_id).p2.x - wp.x;
        float dy2 = sw.wall->getSide(sw.side_id).p2.y - wp.y;
        float xx2 = dx2 * cos(-a) - dy2 * sin(-a);
        float yy2 = dx2 * sin(-a) + dy2 * cos(-a);
        float x2 = getSize().x / 2.f + (yy2 / xx2) * getSize().x;
        RenderR3D::renderTrap(x1, x2, h1, h2, getContext(), getSize(), 0);
    }
}
