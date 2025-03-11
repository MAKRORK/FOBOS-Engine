#pragma once
#include <iostream>
#include <vector>
#include "../Objects/Object.h"
#include "../Visual/Shape.h"
#include <SFML/Graphics.hpp>

using namespace std;

class Render
{
public:
    static void init(sf::RenderWindow *_window);
    static void renderFpsCounter(float d);

    static void render(Shape *s);

    static void render(Circle *c, int context = 0);
    static void render(Circle *c, fv::context cont, int context = 0);

    static void render(Rect *r, int context = 0);
    static void render(Rect *r, fv::context cont, int context = 0);

    static void render(Line *l, int context = 0);
    static void render(Line *l, fv::context cont, int context = 0);

    static void renderAllShapes(fv::renderContext c = fv::renderContext());
    static void renderShapes(vector<Shape *> vec, fv::renderContext c = fv::renderContext());

    static int createNewContext(SMath::vec2 s, fv::Color col = fv::Color::black);

    static void clearContext(int c);
    static void clearAllContext();

    static void resizeContext(SMath::vec2 s, int c);
    static void changeClearColorContext(fv::Color col, int c = 0);

    static void renderContext(SMath::vec2f pos, int c);

    static SMath::vec2 getWindowCord(SMath::vec2 p = SMath::vec2());
    static SMath::vec2 getWindowSize();

private:
    static sf::RenderWindow *window;
    static vector<sf::RenderTexture *> contexts;
    static vector<fv::Color> backgroundColors;
    static sf::Font pixOp;
    static sf::Text fpsCounter;
    static void initFpsCounter();
};
