#include "Player.h"
#include "../../Interfaces/Input.h"
#include "../../Interfaces/SMath.h"
#include "../../Interfaces/Settings.h"
#include "../../Interfaces/ForSFML.h"
#include "../../Global.h"
#include "Colliders/Collider.h"
#include <iostream>
#include <array>

void Player::update()
{
    raycastResult res = Collider::raycast(getWorldPos(), getWorldPos() + getForwardVector() * 300.f, this, true, Global::miniMapCam);
}

void Player::movement(float delta)
{
    SMath::vec2f velMovement = SMath::vec2f(0.f, 0.f);
    if (Input::isPressed(sf::Keyboard::Key::W))
    {
        velMovement += getForwardVector();
    }
    if (Input::isPressed(sf::Keyboard::Key::S))
    {
        velMovement -= getForwardVector();
    }
    if (Input::isPressed(sf::Keyboard::Key::A))
    {
        velMovement += getRightVector();
    }
    if (Input::isPressed(sf::Keyboard::Key::D))
    {
        velMovement -= getRightVector();
    }
    if (Input::isPressed(sf::Keyboard::Key::Left))
    {
        addRot(-7.f * delta * Settings::sensitivity);
    }
    if (Input::isPressed(sf::Keyboard::Key::Right))
    {
        addRot(7.f * delta * Settings::sensitivity);
    }
    addRot(Input::getMouseDelta().x * delta * Settings::sensitivity);
    // cout << Input::getMouseDelta().x << "\n";
    vel += SMath::normalize(velMovement) * speed * delta;
}

void Player::init()
{
    setColliding(true);
}