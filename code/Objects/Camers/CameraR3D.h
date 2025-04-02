#pragma once

#include "Camera.h"
#include "../../Interfaces/SMath.h"
#include "../../Interfaces/Render.h"

struct lineToRender
{
    int x, tex_id;
    float h, dist, aspect;
};

class CameraR3D : public Camera
{
private:
    int fov = 50;
    SMath::vec2 resolution;
    float distance = 1000.f;
    static vector<lineToRender> lines;

public:
    CameraR3D() : Camera() { resolution = Render::getWindowSize() / 2; }
    CameraR3D(SMath::vec2 _size) : Camera(_size) { resolution = Render::getWindowSize() / 4; }
    CameraR3D(SMath::vec2f _pos, SMath::vec2 _size) : Camera(_pos, _size) { resolution = Render::getWindowSize() / 2; }

    void render() override;

    void setResolution(SMath::vec2 _res) { resolution = _res; }
    void setFov(int _fov) { fov = _fov; }
    void setDistance(int _dist) { distance = _dist; }

    SMath::vec2 getResolution() { return resolution; }
    int getFov() { return fov; }
    float getDistance() { return distance; }
};
