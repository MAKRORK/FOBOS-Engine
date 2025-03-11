#pragma once

#include "../Object.h"
#include "Camera.h"

class Camera2D : public Camera
{
private:
public:
    Camera2D() : Camera() {}
    Camera2D(SMath::vec2 _size) : Camera(_size) {}
    Camera2D(SMath::vec2f _pos, SMath::vec2 _size) : Camera(_pos, _size) {}

    void render() override;
};
