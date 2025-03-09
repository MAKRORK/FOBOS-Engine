#include <iostream>
#include <vector>
#include "../Objects/Object.h"

using namespace std;
class Render
{
public:
    static void renderAll(sf::RenderWindow &window);
    static void init();
    static void renderFpsCounter(sf::RenderWindow &window, float d);

private:
    static sf::Font pixOp;
    static sf::Text fpsCounter;
    static void initFpsCounter();
};
