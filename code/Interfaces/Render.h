#pragma once
#include <iostream>
#include <vector>
#include "../Objects/Object.h"
#include "../Visual/Shape.h"
#include <SFML/Graphics.hpp>

using namespace std;

enum ResourseType
{
    TextureSource,
};
struct TileSet
{
    int start;
    int end;
    std::string name;
};

class Render
{
public:
    static void init(sf::RenderWindow *_window);
    static void renderFpsCounter(float d);

    static void render(Shape *s);

    static void render(CircleShape *c, int context = 0);
    static void render(CircleShape *c, fv::context cont, int context = 0);

    static void render(RectShape *r, int context = 0);
    static void render(RectShape *r, fv::context cont, int context = 0);

    static void render(LineShape *l, int context = 0);
    static void render(LineShape *l, fv::context cont, int context = 0);

    static void render(PolygonShape *p, int context = 0);
    static void render(PolygonShape *p, fv::context cont, int context = 0);

    static void renderAllShapes(fv::renderContext c = fv::renderContext());
    static void renderShapes(vector<Shape *> vec, fv::renderContext c = fv::renderContext());

    static int createNewContext(SMath::vec2 s, fv::Color col = fv::Color::black);

    static void clearContext(int c);
    static void clearAllContext();

    static void resizeContext(SMath::vec2 s, int c);
    static void changeClearColorContext(fv::Color col, int c = 0);

    static void renderContext(SMath::vec2f pos, int c);

    static int addResourse(const char *path, ResourseType type, const char *name);
    static void addTexturesFromTileSet(const char *path, const char *name, int h, int v);

    static SMath::vec2 getWindowCord(SMath::vec2 p = SMath::vec2());
    static SMath::vec2 getWindowSize();
    static sf::Texture *getTextureByIndex(int id);
    static int getTextureIndexByName(std::string name);
    static void setMouseVisible(bool t);
    static SMath::vec2 getTexturesFromTileSet(std::string name);

protected:
    static sf::RenderWindow *window;
    static vector<sf::RenderTexture *> contexts;
    static vector<fv::Color> backgroundColors;

private:
    static sf::Font pixOp;
    static sf::Text fpsCounter;
    static vector<sf::Texture *> textures;
    static vector<std::string> textureNames;
    static vector<TileSet> tilesets;
    static void initFpsCounter();
};
