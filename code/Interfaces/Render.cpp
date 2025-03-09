#include "Render.h"
#include "World.h"
#include "Settings.h"

sf::Font Render::pixOp;
sf::Text Render::fpsCounter;

void Render::renderAll(sf::RenderWindow &window)
{
    for (int i = 0; i < World::getObjectCount(); i++)
    {
        World::getObjectByIndex(i)->render(window);
    }
}

void Render::renderFpsCounter(sf::RenderWindow &window, float d)
{
    float fps = 1.f / d;
    fpsCounter.setString(to_string((int)fps));
    window.draw(fpsCounter);
}

void Render::init()
{
    bool res = pixOp.loadFromFile("C:\\Users\\user\\Desktop\\Things\\Projects\\ConsoleTesting\\assets\\fonts\\PixelOperator.ttf");
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
