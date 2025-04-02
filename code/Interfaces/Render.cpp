#include "Render.h"
#include "World.h"
#include "Settings.h"
#include "ForSFML.h"
#include <iostream>
#include <array>
#include "Loger.h"

sf::Font Render::pixOp;
sf::Text Render::fpsCounter;
sf::RenderWindow *Render::window;
vector<sf::RenderTexture *> Render::contexts;
vector<fv::Color> Render::backgroundColors;
vector<sf::Texture *> Render::textures;
vector<std::string> Render::textureNames;
vector<TileSet> Render::tilesets;

void Render::renderFpsCounter(float d)
{
    float fps = 1.f / d;
    Loger::updateFpsRep(fps);
    fpsCounter.setString(to_string((int)fps));
    (*window).draw(fpsCounter);
}

void Render::render(Shape *s)
{
}

void Render::render(CircleShape *c, fv::context cont, int context)
{
    sf::CircleShape sc(c->getScaleRadius() * cont.scale);
    SMath::vec2f p = ((c->getWorldPos() + cont.offset) * c->getScale() * cont.scale) - c->getScaleRadius() * cont.scale;
    if (context)
    {
        p.y = contexts[context - 1]->getSize().y - p.y;
        sc.setScale(1, -1);
    }
    sc.setPosition(forSFML::toSFMLVector(p));
    sc.setFillColor(forSFML::toSFMLColor(c->getColor()));
    if (context == 0)
        window->draw(sc);
    else
    {
        contexts[context - 1]->draw(sc);
    }
}

void Render::render(RectShape *r, fv::context cont, int context)
{
    sf::RectangleShape rs(forSFML::toSFMLVector(r->getScaleSize() * cont.scale));
    SMath::vec2f p = (r->getWorldPos() + cont.offset) * r->getScale() * cont.scale;

    if (context)
    {
        rs.setScale(1, -1);
        p.y = contexts[context - 1]->getSize().y - p.y;
    }
    rs.setPosition(forSFML::toSFMLVector(p));
    rs.setFillColor(forSFML::toSFMLColor(r->getColor()));
    if (context == 0)
        window->draw(rs);
    else
    {
        contexts[context - 1]->draw(rs);
    }
}

void Render::render(RectShape *r, int context)
{
    render(r, fv::context(0.f, 1.f), context);
}

void Render::render(LineShape *l, fv::context cont, int context)
{
    SMath::side pl = SMath::scaledSide(l->getScaleLine(), cont.scale) + (l->getWorldPos() + cont.offset) * l->getScale() * cont.scale;
    if (context)
    {
        pl.p1.y = contexts[context - 1]->getSize().y - pl.p1.y;
        pl.p2.y = contexts[context - 1]->getSize().y - pl.p2.y;
    }
    sf::Vertex line[2] = {
        sf::Vertex{forSFML::toSFMLVector(pl.p1), forSFML::toSFMLColor(l->getColor())},
        sf::Vertex{forSFML::toSFMLVector(pl.p2), forSFML::toSFMLColor(l->getColor())}};
    if (context == 0)
        window->draw(line, 2, sf::PrimitiveType::Lines);
    else
    {
        contexts[context - 1]->draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void Render::render(LineShape *l, int context)
{
    render(l, fv::context(0.f, 1.f), context);
}

void Render::render(PolygonShape *p, int context)
{
    render(p, fv::context(0.f, 1.f), context);
}

void Render::render(PolygonShape *p, fv::context cont, int context)
{
    sf::ConvexShape polygon;
    polygon.setFillColor(forSFML::toSFMLColor(p->getColor()));
    polygon.setPointCount(p->getSize());
    for (int i = 0; i < p->getSize(); i++)
    {
        SMath::vec2f point = p->getScaledPoint(i) * cont.scale + (p->getWorldPos() + cont.offset) * p->getScale() * cont.scale;

        if (context)
        {
            point.y = contexts[context - 1]->getSize().y - point.y;
        }
        polygon.setPoint(i, forSFML::toSFMLVector(point));
    }
    if (context == 0)
        window->draw(polygon);
    else
    {
        contexts[context - 1]->draw(polygon);
    }
}

void Render::renderAllShapes(fv::renderContext c)
{
    for (int i = 0; i < World::getObjectCount(); i++)
    {
        vector<Object *> ss = World::getObjectByIndex(i)->getShapes();
        for (int i = 0; i < ss.size(); i++)
        {
            Shape *s = dynamic_cast<Shape *>(ss[i]);
            s->draw(c);
        }
    }
}

void Render::renderShapes(vector<Shape *> vec, fv::renderContext c)
{
    for (Shape *s : vec)
    {
        s->draw(c);
    }
}

int Render::createNewContext(SMath::vec2 s, fv::Color col)
{
    sf::RenderTexture *c = new sf::RenderTexture;
    c->create(s.x, s.y);
    contexts.push_back(c);
    backgroundColors.push_back(col);
    return contexts.size();
}

void Render::clearContext(int c)
{
    if (c != 0)
    {
        contexts[c - 1]->clear(forSFML::toSFMLColor(backgroundColors[c]));
    }
    else
        window->clear(forSFML::toSFMLColor(backgroundColors[c]));
}

void Render::clearAllContext()
{
    for (int i = 0; i <= contexts.size(); i++)
    {
        clearContext(i);
    }
}

void Render::resizeContext(SMath::vec2 s, int c)
{
    if (c != 0)
    {
        contexts[c]->create(s.x, s.y);
    }
}

void Render::changeClearColorContext(fv::Color col, int c)
{
    backgroundColors[c] = col;
}

void Render::renderContext(SMath::vec2f pos, int c)
{
    if (c != 0)
    {
        sf::Sprite maskedSprite(contexts[c - 1]->getTexture());
        maskedSprite.setPosition(pos.x, pos.y);
        window->draw(maskedSprite);
    }
}

int Render::addResourse(const char *path, ResourseType type, const char *name)
{
    sf::Texture *texture = new sf::Texture;
    switch (type)
    {
    case ResourseType::TextureSource:

        if (!texture->loadFromFile(path))
        {
            return -1;
        }

        textures.push_back(texture);
        textureNames.push_back(name);
        return textures.size() - 1;
        break;

    default:
        break;
    }
    return -1;
}

void Render::addTexturesFromTileSet(const char *path, const char *name, int h, int v)
{
    sf::Image image;
    if (!image.loadFromFile(path))
    {
        return;
    }

    sf::Vector2u size = image.getSize();

    int x = size.x / h;
    int y = size.y / v;
    TileSet ts;
    ts.start = textures.size();
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < h; j++)
        {
            sf::Texture *texture = new sf::Texture;
            if (!texture->loadFromFile(path, sf::IntRect(j * x, i * y, x, y)))
            {
                return;
            }

            textures.push_back(texture);
            string nm = name;
            textureNames.push_back(nm + to_string(i * h + j));
        }
    }
    ts.end = textures.size();

    ts.name = name;
    tilesets.push_back(ts);
    for (int i = 0; i < textureNames.size(); i++)
    {
        cout << textureNames[i] << "\n";
    }
}

SMath::vec2 Render::getWindowCord(SMath::vec2 p)
{
    return forSFML::fromSFMLVectorI(window->getPosition()) + p;
}

SMath::vec2 Render::getWindowSize()
{
    return SMath::vec2(Settings::width, Settings::height);
}

sf::Texture *Render::getTextureByIndex(int id)
{
    return textures[id];
}

int Render::getTextureIndexByName(std::string name)
{
    for (int i = 0; i < textureNames.size(); i++)
    {
        if (textureNames[i] == name)
        {
            return i;
        }
    }
    return -1;
}

void Render::setMouseVisible(bool t)
{
    window->setMouseCursorVisible(t);
}

SMath::vec2 Render::getTexturesFromTileSet(std::string name)
{
    for (TileSet t : tilesets)
    {
        if (t.name == name)
        {
            return SMath::vec2(t.start, t.end);
        }
    }
    return SMath::vec2(0, 0);
}

void Render::render(CircleShape *c, int context)
{
    render(c, fv::context(0.f, 1.f), context);
}

void Render::init(sf::RenderWindow *_window)
{
    window = _window;
    backgroundColors.push_back(fv::Color::black);
    bool res = pixOp.loadFromFile("..\\assets\\fonts\\PixelOperator.ttf");
    if (!res)
    {
        cout << "Error loading font pixelOperator" << endl;
    }
    initFpsCounter();
}

void Render::initFpsCounter()
{
    fpsCounter.setFont(pixOp);
    fpsCounter.setCharacterSize(32);
    fpsCounter.setFillColor(sf::Color::Yellow);
    fpsCounter.setPosition(Settings::width - 70, 10);
}
