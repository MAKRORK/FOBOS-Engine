#include <iostream>

#include <SFML/Graphics.hpp>

#include "code/Objects/Entity/Player.h"
#include "code/Interfaces/Render.h"
#include "code/Objects/Entity/Enemies/Enemy.h"
#include "code/Interfaces/World.h"
#include "code/Interfaces/Settings.h"
#include "code/Objects/Entity/Collider.h"
#include "code/Objects/Blocks/Wall.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(Settings::width, Settings::height), "Huita");

    World::setMap();

    Player player(sf::Vector2f(48.f, 48.f));
    World::addObject(&player);
    Enemy enemy(sf::Vector2f(248.f, 78.f));
    enemy.addChildren(new ColliderCircle(15.f));
    player.addChildren(new ColliderCircle(10.f));
    World::addObject(&enemy);

    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();
    sf::Time currentTime = sf::seconds(0);
    float delta = 0;

    Render::init();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        currentTime = clock.getElapsedTime();
        delta = (currentTime - prevTime).asSeconds();
        if (Settings::vertSync)
        {
            if (delta < 1.f / Settings::maxFrameRate)
            {
                sf::sleep(sf::seconds(1.f / Settings::maxFrameRate - delta));
            }
            delta = 1.f / Settings::maxFrameRate;
        }
        prevTime = currentTime;

        window.clear();
        player.movement(delta);
        player.physics(delta);

        Render::renderAll(window);
        if (Settings::showFpsCounter)
        {
            Render::renderFpsCounter(window, delta);
        }
        window.display();
    }

    return 0;
}