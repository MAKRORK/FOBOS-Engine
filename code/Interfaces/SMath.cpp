#include "SMath.h"
#include <cmath>
sf::Vector2f SMath::normalize(sf::Vector2f vec)
{
    if (vec.x == 0 && vec.y == 0)
    {
        return vec;
    }
    float length = sqrt(vec.x * vec.x + vec.y * vec.y);
    return sf::Vector2f(vec.x / length, vec.y / length);
}

float SMath::length(sf::Vector2f p1, sf::Vector2f p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
float SMath::length(side s)
{
    return SMath::length(s.p1, s.p2);
}
float SMath::length(sf::Vector2f p)
{
    return sqrt(p.x * p.x + p.y * p.y);
}
float SMath::distToLine(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p)
{
    float a = SMath::length(p1, p);
    float b = SMath::length(p2, p);
    float c = SMath::length(p1, p2);
    float p_ = (a + b + c) / 2;
    float S = sqrt(p_ * (p_ - a) * (p_ - b) * (p_ - c));
    return 2 * S / c;
}
float SMath::distToLine(side s, sf::Vector2f p)
{
    return SMath::distToLine(s.p1, s.p2, p);
}
