#pragma once

#include "iostream"
#include <vector>
#include "../../Object.h"
#include "../../../Algoritms/GeometryAlgoritms.h"
class Collider;
struct BVHbranch
{
    SMath::Geometry::RectGeometry rect;
    int childs[2];
    Collider *collider = nullptr;
};

class BVH
{
private:
    std::vector<BVHbranch> branches;
    int createBVH(std::vector<Collider *> &vec, SMath::Geometry::RectGeometry rect);
    void dfsToBVH(std::vector<Collider *> &vec, int start, SMath::Geometry::RectGeometry rect);
    Object *obj = nullptr;

public:
    BVH() {}
    BVH(std::vector<Collider *> &vec) { createNewBVH(vec); }
    void createNewBVH(std::vector<Collider *> &vec);
    std::vector<Collider *> getobjects(SMath::Geometry::RectGeometry rect);
};
