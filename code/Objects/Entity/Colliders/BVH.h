#pragma once

#include "iostream"
#include <vector>
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

public:
    BVH() {}
    BVH(std::vector<Collider *> &vec) { createNewBVH(vec); }
    void createNewBVH(std::vector<Collider *> &vec);
};
