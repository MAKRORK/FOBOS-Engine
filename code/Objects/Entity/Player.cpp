#include "Player.h"
#include "../../Interfaces/Input.h"
#include "../../Interfaces/SMath.h"
#include "../../Interfaces/Settings.h"
#include "../../Interfaces/ForSFML.h"
#include "Collider.h"
#include <iostream>
#include <array>

void Player::render(sf::RenderWindow &window)
{
    std::array line =
        {
            sf::Vertex{forSFML::toSFMLVector(getWorldPos())},
            sf::Vertex{forSFML::toSFMLVector(getWorldPos() + getForwardVector() * 300.f)}};
    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);

    raycastResult res = Collider::raycast(getWorldPos(), getWorldPos() + getForwardVector() * 300.f, this);
    if (res.isColliding)
    {

        for (int i = 0; i < res.collidedObjects.size(); i++)
        {
            for (int j = 0; j < res.collidedObjects[i].points.size(); j++)
            {
                sf::CircleShape shape(5.f);
                shape.setFillColor(sf::Color::Red);
                shape.setPosition(forSFML::toSFMLVector(res.collidedObjects[i].points[j] - SMath::vec2f(5.f, 5.f)));
                window.draw(shape);
            }
        }
    }
}

void Player::movement(float delta)
{
    SMath::vec2f velMovement = SMath::vec2f(0.f, 0.f);
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
}