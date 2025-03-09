#include "Player.h"
#include "../../Interfaces/Input.h"
#include "../../Interfaces/SMath.h"
#include "../../Interfaces/Settings.h"
#include "Collider.h"
#include <iostream>
#include <array>

void Player::render(sf::RenderWindow &window)
{
    shape.setPosition(getPos() - sf::Vector2f(10.f, 10.f));
    window.draw(shape);
    std::array line =
        {
            sf::Vertex{getWorldPos()},
            sf::Vertex{getWorldPos() + getForwardVector() * 300.f}};
    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);

    raycastResult res = Collider::raycast(getWorldPos(), getWorldPos() + getForwardVector() * 300.f);
    if (res.isColliding)
    {

        for (int i = 0; i < res.collidedObjects.size(); i++)
        {
            for (int j = 0; j < res.collidedObjects[i].points.size(); j++)
            {
                sf::CircleShape shape(5.f);
                shape.setFillColor(sf::Color::Red);
                shape.setPosition(res.collidedObjects[i].points[j] - sf::Vector2f(5.f, 5.f));
                window.draw(shape);
            }
        }
    }
}

void Player::movement(float delta)
{
    sf::Vector2f velMovement = sf::Vector2f(0.f, 0.f);
    if (Input::isPressed(sf::Keyboard::Key::W))
    {
        velMovement.y -= 1.f;
    }
    if (Input::isPressed(sf::Keyboard::Key::S))
    {
        velMovement.y += 1.f;
    }
    if (Input::isPressed(sf::Keyboard::Key::A))
    {
        velMovement.x -= 1.f;
    }
    if (Input::isPressed(sf::Keyboard::Key::D))
    {
        velMovement.x += 1.f;
    }
    if (Input::isPressed(sf::Keyboard::Key::Left))
    {
        addRot(-1.f * delta * Settings::sensitivity);
    }
    if (Input::isPressed(sf::Keyboard::Key::Right))
    {
        addRot(1.f * delta * Settings::sensitivity);
    }
    vel += SMath::normalize(velMovement) * speed * delta;
}

void Player::init()
{
    setColliding(true);
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::Green);
}