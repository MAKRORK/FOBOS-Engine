
#pragma once
#include "R3DObject.h"
#include "../../Interfaces/SMath.h"
#include "../Entity/Colliders/Collider.h"
#include "../../Visual/Shape.h"
#include <iostream>

class Wall;

struct sideWall
{
    Wall *wall = nullptr;
    int side_id;
    sideWall() {}
    sideWall(Wall *_w, int id) : wall(_w), side_id(id) {}
};

class Wall : public R3DObject
{
private:
    vector<int> textures;
    vector<SMath::vec2f> points;
    Collider *wallCollider = nullptr;
    Shape *wallShape = nullptr;
    static vector<Wall *> walls;

protected:
    void setWallCollider(Collider *_col);
    void setWallShape(Shape *_shp);

public:
    Wall() : R3DObject() { walls.push_back(this); }
    Wall(SMath::vec2f _pos) : R3DObject(_pos) { walls.push_back(this); }

    void setSize(int _size);
    void setPoint(int id, SMath::vec2f _p);
    int getSize();
    int getTextureIndex(int side_id);

    void setTextureById(int side_id, int texture_id);
    void setTextureByName(int side_id, std::string name);
    void setTextureForAllById(int texture_id);
    void setTextureForAllByName(std::string name);
    void create();

    virtual SMath::vec2f getNormal(int id);
    Collider *getWallCollider();
    Shape *getWallShape();

    SMath::side getSide(int id);

    static vector<sideWall> getSidesInFov(SMath::vec2f pos, float dist, float fov, float angle);
};
