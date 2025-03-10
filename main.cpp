#include <iostream>

#include <SFML/Graphics.hpp>

#include "code/Objects/Entity/Player.h"
#include "code/Interfaces/Render.h"
#include "code/Objects/Entity/Enemies/Enemy.h"
#include "code/Interfaces/World.h"
#include "code/Interfaces/Settings.h"
#include "code/Interfaces/SMath.h"
#include "code/Objects/Entity/Collider.h"
#include "code/Visual/Shape.h"

#include <array>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(Settings::width, Settings::height), "Huita");

    World::setMap();

    Player player(SMath::vec2f(320.f + 34.f, 78.f + 34.f));
    player.addChildren(new Circle(10.f, fv::Color::green));
    World::addObject(&player);
    Enemy enemy(SMath::vec2f(248.f, 78.f));
    enemy.addChildren(new Circle(15.f, fv::Color::blue));
    enemy.addChildren(new ColliderCircle(15.f));
    player.addChildren(new ColliderCircle(10.f));
    World::addObject(&enemy);

    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();
    sf::Time currentTime = sf::seconds(0);
    float delta = 0;

    Render::init(&window);
    SMath::vec2f f = 2.f * SMath::vec2f(1, 2);
    std::cout << f.x << "  " << f.y << "\n";

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

        Render::renderAllShapes();
        player.render(window);
        if (Settings::showFpsCounter)
        {
            Render::renderFpsCounter(delta);
        }

        window.display();
    }

    return 0;
}