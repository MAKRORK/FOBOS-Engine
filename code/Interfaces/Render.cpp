#include "Render.h"
#include "World.h"
#include "Settings.h"
#include "ForSFML.h"

sf::Font Render::pixOp;
sf::Text Render::fpsCounter;
sf::RenderWindow *Render::window;

void Render::renderFpsCounter(float d)
{
    float fps = 1.f / d;
    fpsCounter.setString(to_string((int)fps));
    (*window).draw(fpsCounter);
}

void Render::render(Shape *s)
{
}

void Render::render(Circle *c, fv::context cont)
{
    sf::CircleShape sc(c->getScaleRadius() * cont.scale);
    sc.setPosition(forSFML::toSFMLVector((c->getWorldPos() + cont.offset) - c->getScaleRadius()));
    sc.setFillColor(forSFML::toSFMLColor(c->getColor()));
    window->draw(sc);
}

void Render::render(Rect *r, fv::context cont)
{
    sf::RectangleShape rs(forSFML::toSFMLVector(r->getScaleSize() * cont.scale));
    rs.setPosition(forSFML::toSFMLVector(r->getWorldPos() + cont.offset));
    rs.setFillColor(forSFML::toSFMLColor(r->getColor()));
    window->draw(rs);
}

void Render::render(Rect *r)
{
    render(r, fv::context(0.f, 1.f));
}

void Render::renderAllShapes()
{
    for (int i = 0; i < World::getObjectCount(); i++)
    {
        vector<Object *> ss = World::getObjectByIndex(i)->getShapes();
        for (int i = 0; i < ss.size(); i++)
        {
            Shape *s = dynamic_cast<Shape *>(ss[i]);
            s->draw();
        }
    }
}

void Render::render(Circle *c)
{
    render(c, fv::context(0.f, 1.f));
}

void Render::init(sf::RenderWindow *_window)
{
    window = _window;
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
