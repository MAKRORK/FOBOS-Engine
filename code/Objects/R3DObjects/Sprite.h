#pragma once
#include "R3DObject.h"
#include "../GraphicsObjects/Texture.h"

class Sprite;

struct SpriteToRender
{
    float dist;
    Sprite *sprite;
    float w, h, x;
};

class Sprite : public R3DObject
{
private:
    Texture *texture = nullptr;
    float radius = 40.f;
    static vector<Sprite *> sprites;
    float heigth = 80.f;

public:
    Sprite() : R3DObject() { sprites.push_back(this); }
    Sprite(SMath::vec2f _pos, float _radius = 10.f, Texture *_tex = nullptr) : R3DObject(_pos)
    {
        sprites.push_back(this);
        radius = _radius;
        texture = _tex;
    }

    int getRadius() { return radius; }
    int getTextureIndex() { return texture->getID(); }
    static vector<SpriteToRender> getSpritesToRender(SMath::vec2f pos, float dist, float fov, float angle);

    void setRadius(float _radius)
    {
        radius = _radius;
    }
    void setTexture(Texture *_tex)
    {
        texture = _tex;
    }
};
