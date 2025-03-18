#pragma once
#include <iostream>
#include <vector>
#include "../Interfaces/SMath.h"
namespace SMath
{
    namespace Geometry
    {
        struct CircleGeometry
        {
            SMath::vec2f center;
            double radius;
        };
        struct RectGeometry
        {
            vec2f tl;
            vec2f br;
            RectGeometry() : tl(0.f), br(0.f) {}
            RectGeometry(vec2f _tl, vec2f _br) : tl(_tl), br(_br) {}
        };
        CircleGeometry circleFromTwoPoints(const SMath::vec2f &p1, const SMath::vec2f &p2);
        CircleGeometry trivialCircle(const std::vector<SMath::vec2f> &R);
        CircleGeometry welzl(std::vector<SMath::vec2f> &P, std::vector<SMath::vec2f> R, int n);
        CircleGeometry findMinCircle(std::vector<SMath::vec2f> &points);
        CircleGeometry findMinCircleCopy(std::vector<SMath::vec2f> points);
        SMath::vec2f getCross(SMath::vec2f p);
        SMath::vec2f getNormal(SMath::vec2f p1, SMath::vec2f p2, SMath::vec2f c);
        SMath::vec2f getNormal(side s, SMath::vec2f c);
    }
}