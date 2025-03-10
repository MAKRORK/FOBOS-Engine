#include <iostream>
#include <vector>
#include "../Objects/Object.h"
#include "../Visual/Shape.h"

using namespace std;
class Render
{
public:
    static void init(sf::RenderWindow *_window);
    static void renderFpsCounter(float d);
    static void render(Shape *s);
    static void render(Circle *c);
    static void render(Circle *c, fv::context cont);
    static void render(Rect *r);
    static void render(Rect *r, fv::context cont);
    static void renderAllShapes();

private:
    static sf::RenderWindow *window;
    static sf::Font pixOp;
    static sf::Text fpsCounter;
    static void initFpsCounter();
};
