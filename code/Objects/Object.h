#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <iostream>

class Object
{
public:
    Object();
    Object(sf::Vector2f _pos);

    virtual void render(sf::RenderWindow &window) {}

    void setPos(sf::Vector2f _pos);
    void setRot(float _rot);
    void addPos(sf::Vector2f _pos);
    void addRot(float _rot);

    sf::Vector2f getPos();
    float getRot();
    sf::Vector2f getWorldPos();
    float getWorldRot();

    void addChildren(Object *child);

    void setParent(Object *_parent);
    Object *getParent();

    Object *getColliderObject();

    sf::Vector2f getForwardVector();

private:
    Object *collider = nullptr;
    Object *parent = nullptr;
    sf::Vector2f pos;
    float rot;
    std::vector<Object *> childrens;
};
