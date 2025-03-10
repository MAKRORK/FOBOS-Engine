#include "ForSFML.h"

sf::Vector2f forSFML::toSFMLVector(SMath::vec2f v)
{
    return sf::Vector2f(v.x, v.y);
}
sf::Color forSFML::toSFMLColor(fv::Color c)
{
    return sf::Color(c.r, c.g, c.b, c.a);
}
