#include "World.h"
#include "SMath.h"
#include "../Objects/R3DObjects/WallRect.h"
#include "../Visual/Shape.h"

std::vector<Object *> World::objects;
string *World::map;
int World::mapWidth = 20;
int World::mapHeight = 12;
int **World::mapBlocks;
Camera *World::mainCamera = nullptr;

void World::setMap()
{
    map = new string[12];
    map[0] = "####################";
    map[1] = "#                  #";
    map[2] = "#           ########";
    map[3] = "######      #      #";
    map[4] = "#           #      #";
    map[5] = "#           #      #";
    map[6] = "######  #####      #";
    map[7] = "#                  #";
    map[8] = "#                  #";
    map[9] = "#   ######         #";
    map[10] = "#                  #";
    map[11] = "####################";
    // mapBlocks = new int *[mapHeight];
    for (int i = 0; i < mapHeight; i++)
    {
        // mapBlocks[i] = new int[mapWidth];
        for (int j = 0; j < mapWidth; j++)
        {
            if (map[i][j] == '#')
            {
                WallRect *w = new WallRect(SMath::vec2f(j * 32.f, i * 32.f), SMath::vec2f(32.f, 32.f));
                w->setTextureForAllByName("wall1");
                int t = addObject(w);
                // RectShape *r = new RectShape(SMath::vec2f(32.f, 32.f));
                // r->setColor(fv::Color::white);
                // getObjectByIndex(t)->addChildren(r);
            }
        }
    }
}

int World::getMapWidth()
{
    return mapWidth;
}

int World::getMapHeight()
{
    return mapHeight;
}

Camera *World::getMainCamera()
{
    return mainCamera;
}

void World::setMainCamera(Camera *cam)
{
    mainCamera = cam;
}

void World::clear()
{
    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
    objects.clear();
}

void World::removeObject(Object *obj)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (obj == objects[i])
        {
            objects.erase(objects.begin() + i);
            break;
        }
    }
    delete obj;
}

int World::addObject(Object *obj)
{
    objects.push_back(obj);
    // obj->setID(objects.size() - 1);
    return objects.size() - 1;
}

int World::getObjectCount()
{
    return objects.size();
}

Object *World::getObjectByIndex(int index)
{
    return objects[index];
}

Object *World::getBlock(int x, int y)
{
    return NULL;
}
