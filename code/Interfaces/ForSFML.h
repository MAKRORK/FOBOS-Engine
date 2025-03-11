#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "SMath.h"
#include "../Visual/VisualStructs.h"

namespace forSFML
{
    sf::Vector2f toSFMLVector(SMath::vec2f v);
    sf::Vector2i toSFMLVectorI(SMath::vec2 v);
    sf::Color toSFMLColor(fv::Color c);
    SMath::vec2 fromSFMLVectorI(sf::Vector2i v);
};