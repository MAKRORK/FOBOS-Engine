#include "World.h"
#include "../Objects/Blocks/Wall.h"

std::vector<Object *> World::objects;
string *World::map;
int World::mapWidth = 20;
int World::mapHeight = 12;
int **World::mapBlocks;

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
    mapBlocks = new int *[mapHeight];
    for (int i = 0; i < mapHeight; i++)
    {
        mapBlocks[i] = new int[mapWidth];
        for (int j = 0; j < mapWidth; j++)
        {
            if (map[i][j] == '#')
            {
                mapBlocks[i][j] = addObject(new Wall(sf::Vector2f(j * 32, i * 32)));
            }
            else
            {
                mapBlocks[i][j] = -1;
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

int World::addObject(Object *obj)
{
    objects.push_back(obj);
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
