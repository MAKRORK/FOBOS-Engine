#include <iostream>

#include <SFML/Graphics.hpp>

#include "code/Objects/Entity/Player.h"
#include "code/Interfaces/Render.h"
#include "code/Objects/Entity/Enemies/Enemy.h"
#include "code/Interfaces/World.h"
#include "code/Interfaces/Settings.h"
#include "code/Interfaces/SMath.h"
#include "code/Interfaces/Loger.h"
#include "code/Objects/Entity/Colliders/Collider.h"
#include "code/Objects/Entity/Colliders/ColliderPolygon.h"
#include "code/Objects/Entity/Colliders/ColliderCircle.h"
#include "code/Visual/Shape.h"
#include "code/Objects/Camers/Camera2D.h"
#include "code/Objects/Camers/CameraR3D.h"
#include "code/Interfaces/Input.h"
#include "code/Global.h"
#include "code/Algoritms/GeometryAlgoritms.h"

#include <array>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(Settings::width, Settings::height), "Huita");

    World::setMap();
    Render::init(&window);
    Input::init();
    Player player(SMath::vec2f(320.f + 34.f, 78.f + 34.f));
    player.addChildren(new CircleShape(10.f, fv::Color::white));
    World::addObject(&player);

    Global::miniMapCam = new Camera2D(SMath::vec2f(0.f), SMath::vec2(760, 640));
    Global::miniMapCam->NewRenderContext();
    Global::miniMapCam->setBackgroundColor(fv::Color(76, 230, 114));
    Global::miniMapCam->setScreenPos(SMath::vec2f(Settings::width - 760.f, Settings::height - 640.f));

    Camera *cam = new CameraR3D();
    cam->setBackgroundColor(fv::Color::black);

    player.addChildren(cam);

    player.addChildren(Global::miniMapCam);

    World::setMainCamera(cam);

    Enemy enemy(SMath::vec2f(248.f, 78.f));
    enemy.addChildren(new CircleShape(15.f, fv::Color::blue));
    enemy.addChildren(new ColliderCircle(15.f));
    player.addChildren(new ColliderCircle(10.f));
    World::addObject(&enemy);

    // Input::setMouseCentered(true);
    Object *o = new Object();
    PolygonShape *pol = new PolygonShape(5);
    pol->setPoint(0, SMath::vec2f(0.f));
    pol->setPoint(1, SMath::vec2f(30.f, 10.f));
    pol->setPoint(2, SMath::vec2f(40.f));
    pol->setPoint(3, SMath::vec2f(10.f, 80.f));
    pol->setPoint(4, SMath::vec2f(0.f, 40.f));
    pol->setColor(fv::Color::yellow);
    o->setPos(SMath::vec2f(500.f, 250.f));

    ColliderPolygon *cpol = new ColliderPolygon(5);
    cpol->setPoint(0, SMath::vec2f(0.f));
    cpol->setPoint(1, SMath::vec2f(30.f, 10.f));
    cpol->setPoint(2, SMath::vec2f(40.f));
    cpol->setPoint(3, SMath::vec2f(10.f, 80.f));
    cpol->setPoint(4, SMath::vec2f(0.f, 40.f));
    o->addChildren(pol);
    o->addChildren(cpol);
    World::addObject(o);

    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();
    sf::Time currentTime = sf::seconds(0);
    float delta = 0;
    Collider::createBVH();
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

        Input::update();

        Render::clearAllContext();
        player.movement(delta);
        player.physics(delta);

        player.update();
        Global::miniMapCam->render();
        cam->render();
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
        if (Settings::showFpsCounter)
        {
            Render::renderFpsCounter(delta);
        }
        window.display();
    }
    Loger::report();
    World::clear();
    return 0;
}