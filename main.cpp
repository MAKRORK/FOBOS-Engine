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
#include "code/Objects/Camers/CameraQ3D.h"
#include "code/Interfaces/Input.h"
#include "code/Global.h"
#include "code/Algoritms/GeometryAlgoritms.h"
#include "code/Objects/R3DObjects/Wall.h"

#include <array>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(Settings::width, Settings::height), "Huita");
    Render::init(&window);
    Render::addResourse("C:\\Users\\user\\Desktop\\Things\\Projects\\ConsoleTesting\\assets\\img\\WallTextures\\2.png", ResourseType::Texture, "wall1");
    Render::addResourse("C:\\Users\\user\\Desktop\\Things\\Projects\\ConsoleTesting\\assets\\img\\WallTextures\\3.png", ResourseType::Texture, "wall2");

    World::setMap();

    Input::init();
    Player player(SMath::vec2f(320.f + 34.f, 78.f + 34.f));
    player.addChildren(new CircleShape(10.f, fv::Color::white));
    World::addObject(&player);

    Global::miniMapCam = new Camera2D(SMath::vec2f(0.f), SMath::vec2(360, 300));
    Global::miniMapCam->NewRenderContext();
    Global::miniMapCam->setBackgroundColor(fv::Color(76, 230, 114));
    Global::miniMapCam->setScreenPos(SMath::vec2f(Settings::width - 360.f, Settings::height - 300.f));

    Camera *cam = new CameraR3D(SMath::vec2(Settings::width, Settings::height));
    cam->setBackgroundColor(fv::Color::black);

    player.addChildren(cam);

    player.addChildren(Global::miniMapCam);

    World::setMainCamera(cam);

    Collider *cccc = new ColliderCircle(10.f);

    player.addChildren(cccc);
    // World::addObject(&enemy);

    Input::setMouseCentered(true);
    Render::setMouseVisible(false);
    Wall *w = new Wall();
    w->setSize(5);

    w->setPoint(0, SMath::vec2f(0.f));
    w->setPoint(1, SMath::vec2f(30.f, 10.f));
    w->setPoint(2, SMath::vec2f(40.f));
    w->setPoint(3, SMath::vec2f(10.f, 80.f));
    w->setPoint(4, SMath::vec2f(0.f, 40.f));
    w->create();

    w->setPos(SMath::vec2f(500.f, 250.f));
    w->setTextureForAllByName("wall2");
    w->setTextureByName(1, "wall1");
    World::addObject(w);

    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();
    sf::Time currentTime = sf::seconds(0);
    float delta = 0;
    Collider::createBVH();

    cccc->setIsDynamic(true);

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
        cam->render();
        Global::miniMapCam->render();

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