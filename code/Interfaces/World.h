#pragma once
#include "../Objects/Object.h"
#include <vector>
#include <iostream>
#include <string>
#include "../Objects/Camers/Camera.h"

using namespace std;

class World
{
public:
    static int addObject(Object *obj);
    static int getObjectCount();
    static Object *getObjectByIndex(int index);
    static Object *getBlock(int x, int y);
    static void setMap();
    static int getMapWidth();
    static int getMapHeight();
    static Camera *getMainCamera();
    static void setMainCamera(Camera *cam);
    static void clear();

private:
    static std::vector<Object *> objects;
    static string *map;
    static int mapWidth;
    static int mapHeight;
    static int **mapBlocks;
    static Camera *mainCamera;
};
