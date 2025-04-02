#pragma once
#include <iostream>
#include "../../Interfaces/Render.h"
#define PLACEHOLDER_TEXTURE_ID 0

class Texture
{
private:
    int id = -1;

public:
    Texture() {}
    Texture(int _id) : id(_id) {}
    Texture(std::string _name) : id(Render::getTextureIndexByName(_name)) {}

    virtual int getID() { return id; }

    void setID(int _id) { id = _id; }
};
