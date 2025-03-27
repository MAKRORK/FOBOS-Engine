#pragma once
#include "CameraR3D.h"
#include "../R3DObjects/Wall.h"

class CameraQ3D : public CameraR3D
{
private:
public:
    CameraQ3D() : CameraR3D() {}
    CameraQ3D(SMath::vec2 _size) : CameraR3D(_size) {}
    CameraQ3D(SMath::vec2 _pos, SMath::vec2 _size) : CameraR3D(_pos, _size) {}

    void render() override;
};
