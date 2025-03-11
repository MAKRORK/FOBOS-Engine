#include "Render.h"
#include "World.h"
#include "Settings.h"
#include "ForSFML.h"
#include <iostream>
#include <array>

sf::Font Render::pixOp;
sf::Text Render::fpsCounter;
sf::RenderWindow *Render::window;
vector<sf::RenderTexture *> Render::contexts;
vector<fv::Color> Render::backgroundColors;

void Render::renderFpsCounter(float d)
{
    float fps = 1.f / d;
    fpsCounter.setString(to_string((int)fps));
    (*window).draw(fpsCounter);
}

void Render::render(Shape *s)
{
}

void Render::render(Circle *c, fv::context cont, int context)
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

void Render::render(Rect *r, fv::context cont, int context)
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

void Render::render(Rect *r, int context)
{
    render(r, fv::context(0.f, 1.f), context);
}

void Render::render(Line *l, fv::context cont, int context)
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

void Render::render(Line *l, int context)
{
    render(l, fv::context(0.f, 1.f), context);
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
        // sf::RenderStates states;
        // states.transform.scale(1, -1);
        // states.transform.translate(0, contexts[c - 1]->getSize().y);
        window->draw(maskedSprite);
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

void Render::render(Circle *c, int context)
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
