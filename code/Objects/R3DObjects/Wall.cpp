#include "Wall.h"
#include <iostream>
#include "../Entity/Colliders/Collider.h"
#include "../../Interfaces/ForSFML.h"
#include "../../Visual/Shape.h"
#include "../Entity/Colliders/ColliderRect.h"
#include "../../Interfaces/Render.h"
#include "../Entity/Colliders/ColliderPolygon.h"
#include "../../Visual/Shape.h"
#include "../../Global.h"
#include <cmath>

vector<Wall *> Wall::walls;

void Wall::setWallCollider(Collider *_col)
{
    if (wallCollider)
    {
        replaceChildren(wallCollider, _col);
    }
    else
    {
        addChildren(_col);
    }
    wallCollider = _col;
}

void Wall::setWallShape(Shape *_shp)
{
    if (wallShape)
    {
        replaceChildren(wallShape, _shp);
    }
    else
    {
        addChildren(_shp);
    }
    wallShape = _shp;
}

SMath::vec2f Wall::getNormal(int id)
{
    return wallCollider->getNormal(id);
}

Collider *Wall::getWallCollider()
{
    return wallCollider;
}

Shape *Wall::getWallShape()
{
    return wallShape;
}

void Wall::setSize(int _size)
{
    points.resize(_size);
    textures.resize(_size);
}

void Wall::setPoint(int id, SMath::vec2f _p)
{
    points[id] = _p;
}

int Wall::getSize()
{
    return points.size();
}

int Wall::getTextureIndex(int side_id)
{
    return textures[side_id];
}

void Wall::setTextureById(int side_id, int texture_id)
{
    textures[side_id] = texture_id;
}

void Wall::setTextureByName(int side_id, std::string name)
{
    textures[side_id] = Render::getTextureIndexByName(name);
}

void Wall::setTextureForAllById(int texture_id)
{
    for (int i = 0; i < textures.size(); i++)
    {
        textures[i] = texture_id;
    }
}

void Wall::setTextureForAllByName(std::string name)
{
    int id = Render::getTextureIndexByName(name);
    for (int i = 0; i < textures.size(); i++)
    {
        textures[i] = id;
    }
}

void Wall::create()
{
    ColliderPolygon *col = new ColliderPolygon();
    PolygonShape *shp = new PolygonShape();
    col->setSize(points.size());
    shp->setSize(points.size());
    for (int i = 0; i < points.size(); i++)
    {
        col->setPoint(i, points[i]);
        shp->setPoint(i, points[i]);
    }
    shp->setColor(fv::Color::yellow);
    setWallCollider(col);
    setWallShape(shp);
}

SMath::side Wall::getSide(int id)
{
    return SMath::side(points[id] + getWorldPos(), points[(id + 1) % points.size()] + getWorldPos());
}

vector<sideWall> Wall::getSidesInFov(SMath::vec2f pos, float dist, float fov, float angle)
{
    float dd = dist * dist;
    float f = SMath::deg2rad(fov) / 2.f;
    SMath::vec2f fvt = SMath::getVectorFromAngle(angle);
    SMath::vec2f fvmn = SMath::getVectorFromAngle(angle - f);
    SMath::vec2f fvmx = SMath::getVectorFromAngle(angle + f);
    float scb = SMath::scalar(normalize(fvt), normalize(SMath::getVectorFromAngle(angle + f)));
    vector<sideWall> result;
    for (Wall *w : walls)
    {
        for (int i = 0; i < w->getSize(); i++)
        {
            if (SMath::scalar(w->getNormal(i), fvmn) < 0 || SMath::scalar(w->getNormal(i), fvmx) < 0)
            {
                float sc = SMath::scalar(fvt, SMath::normalize(w->getSide(i).p1 - pos));
                if (SMath::sqrLength(w->getSide(i).p1, pos) < dd && sc > scb)
                {

                    Global::miniMapCam->addToRender(new CircleShape(w->getSide(i).p1, 5.f, fv::Color::blue));
                    Global::miniMapCam->addToRender(new LineShape(w->getSide(i), fv::Color::red));
                    result.push_back(sideWall(w, i));
                }
                else if (SMath::sqrLength(w->getSide(i).p2, pos) < dd)
                {
                    float sc = SMath::scalar(fvt, SMath::normalize(w->getSide(i).p2 - pos));
                    // cout << "2\n";
                    if (sc > scb)
                    {
                        Global::miniMapCam->addToRender(new CircleShape(w->getSide(i).p2, 5.f, fv::Color::blue));
                        Global::miniMapCam->addToRender(new LineShape(w->getSide(i), fv::Color::red));
                        result.push_back(sideWall(w, i));
                    }
                }
            }
        }
    }
    return result;
}
