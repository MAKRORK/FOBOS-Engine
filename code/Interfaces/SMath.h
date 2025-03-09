#pragma once
#include <SFML/System/Vector2.hpp>
#include "../Objects/Entity/Collider.h"

namespace SMath
{
    sf::Vector2f normalize(sf::Vector2f vec);
    float distToLine(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p);
    float length(sf::Vector2f p1, sf::Vector2f p2);
    float distToLine(side s, sf::Vector2f p);
    float length(side s);
    float length(sf::Vector2f p);
}
