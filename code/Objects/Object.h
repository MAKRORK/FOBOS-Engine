#pragma once
#include "../Interfaces/SMath.h"
#include <vector>
#include <iostream>

class Object
{
public:
    Object();
    Object(SMath::vec2f _pos);
    virtual ~Object();
    virtual void update() {}

    void setPos(SMath::vec2f _pos);
    void setRot(float _rot);
    void addPos(SMath::vec2f _pos);
    void addRot(float _rot);

    float getScale();
    float getWorldScale();
    void setScale(float _s);

    SMath::vec2f getPos();
    float getRot();
    SMath::vec2f getWorldPos();
    float getWorldRot();

    virtual int addChildren(Object *child);
    void replaceChildren(Object *child, Object *new_child);

    void setParent(Object *_parent);
    Object *getParent();

    Object *getColliderObject();

    Object *getChildrenByIndex(int i);

    std::vector<Object *> getChildrens();

    std::vector<Object *> getShapes();

    SMath::vec2f getForwardVector();
    SMath::vec2f getRightVector();

private:
    Object *collider = nullptr;
    Object *parent = nullptr;
    SMath::vec2f pos;
    float rot;
    float scale = 1.f;
    std::vector<Object *> childrens;
};
