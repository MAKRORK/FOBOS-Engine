#include "ForSFML.h"

sf::Vector2f forSFML::toSFMLVector(SMath::vec2f v)
{
    return sf::Vector2f(v.x, v.y);
}
sf::Vector2i forSFML::toSFMLVectorI(SMath::vec2 v)
{
    return sf::Vector2i(v.x, v.y);
}
sf::Color forSFML::toSFMLColor(fv::Color c)
{
    return sf::Color(c.r, c.g, c.b, c.a);
}

SMath::vec2 forSFML::fromSFMLVectorI(sf::Vector2i v)
{
    return SMath::vec2(v.x, v.y);
}
