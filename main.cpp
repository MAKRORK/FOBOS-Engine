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
#include "code/Objects/Camers/Camera2D.h"
#include "code/Interfaces/Input.h"

#include <array>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(Settings::width, Settings::height), "Huita");

    World::setMap();
    Render::init(&window);
    Input::init();
    Player player(SMath::vec2f(320.f + 34.f, 78.f + 34.f));
    player.addChildren(new Circle(10.f, fv::Color::white));
    World::addObject(&player);
    Camera2D *cam = new Camera2D(SMath::vec2f(0.f), SMath::vec2(480, 320));
    cam->NewRenderContext();
    cam->setBackgroundColor(fv::Color(76, 230, 114));
    cam->setScreenPos(SMath::vec2f(Settings::width - 480.f, Settings::height - 320.f));
    player.addChildren(cam);
    World::setMainCamera(cam);
    Enemy enemy(SMath::vec2f(248.f, 78.f));
    enemy.addChildren(new Circle(15.f, fv::Color::blue));
    enemy.addChildren(new ColliderCircle(15.f));
    player.addChildren(new ColliderCircle(10.f));
    World::addObject(&enemy);

    // Input::setMouseCentered(true);

    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();
    sf::Time currentTime = sf::seconds(0);
    float delta = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
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

        Input::update();

        Render::clearAllContext();
        player.movement(delta);
        player.physics(delta);

        player.update();
        cam->render();
        if (Settings::showFpsCounter)
        {
            Render::renderFpsCounter(delta);
        }
        window.display();
    }

    return 0;
}