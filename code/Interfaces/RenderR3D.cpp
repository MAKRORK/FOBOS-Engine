#include "RenderR3D.h"
#include "ForSFML.h"
#include <cmath>

void RenderR3D::renderRayLine(int x, float h, int context, fv::context cont, SMath::vec2 res, SMath::vec2f size, float dist, float aspect, int texture_id)
{
    // sf::RectangleShape rect;

    fv::Color color;
    int c = SMath::clamp((int)((255 * 100) / dist), 45, 255);
    color = fv::Color(c);

    sf::Sprite sprite;
    sprite.setTexture(*getTextureByIndex(texture_id));

    // rect.setFillColor(forSFML::toSFMLColor(color));
    int asp = ceil(size.x / res.x);
    sprite.setPosition(forSFML::toSFMLVector((SMath::vec2f(x * asp, (size.y / 2.f) - h / 2) + cont.offset) * cont.scale));
    sf::Vector2u texSize = getTextureByIndex(texture_id)->getSize();
    sprite.setTextureRect(sf::IntRect(ceil(aspect * texSize.x), 0, 1, texSize.y));
    sprite.setScale(4.f, (h * cont.scale) / texSize.y);
    sprite.setColor(forSFML::toSFMLColor(color));
    // rect.setSize(sf::Vector2f(asp, h * cont.scale));
    if (!context)
    {
        window->draw(sprite);
    }
    else
    {
        contexts[context]->draw(sprite);
    }
}

void RenderR3D::renderTrap(float x1, float x2, float h1, float h2, fv::context cont, SMath::vec2f size, int texture_id)
{
    sf::VertexArray quad(sf::Quads, 4);
    sf::Vector2u texSize = getTextureByIndex(texture_id)->getSize();

    quad[0].position = sf::Vector2f(forSFML::toSFMLVector(((SMath::vec2f(x1, (size.y / 2.f) - h1 / 2)) + cont.offset) * cont.scale));
    quad[3].position = sf::Vector2f(forSFML::toSFMLVector(((SMath::vec2f(x1, (size.y / 2.f) + h1 / 2)) + cont.offset) * cont.scale));
    quad[1].position = sf::Vector2f(forSFML::toSFMLVector(((SMath::vec2f(x2, (size.y / 2.f) - h2 / 2)) + cont.offset) * cont.scale));
    quad[2].position = sf::Vector2f(forSFML::toSFMLVector(((SMath::vec2f(x2, (size.y / 2.f) + h2 / 2)) + cont.offset) * cont.scale));

    quad[0].texCoords = sf::Vector2f(0.f, 0.f);
    quad[1].texCoords = sf::Vector2f(texSize.x, 0.f);
    quad[2].texCoords = sf::Vector2f(texSize.x, texSize.y);
    quad[3].texCoords = sf::Vector2f(0.f, texSize.y);
    sf::RenderStates states;
    states.texture = getTextureByIndex(texture_id);
    window->draw(quad, states);
}

void RenderR3D::renderSky(float angle, int texture_id, int context, fv::context cont, SMath::vec2f size)
{
    sf::Vector2u texSize = getTextureByIndex(texture_id)->getSize();
    float ofset = SMath::correctAngle(angle) / (2 * SMath::pi) * texSize.x;

    sf::Sprite sprite;
    getTextureByIndex(texture_id)->setRepeated(true);
    sprite.setTexture(*getTextureByIndex(texture_id));
    sprite.setPosition(sf::Vector2f(0.f, 0.f));
    sprite.setTextureRect(sf::IntRect(ceil(ofset), 0, size.x, texSize.y));

    window->draw(sprite);
}

void RenderR3D::renderFloor(int context, fv::context cont, SMath::vec2f size)
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(size.x, size.y / 2));
    rect.setFillColor(forSFML::toSFMLColor(fv::Color(43)));
    rect.setPosition(sf::Vector2f(0.f, size.y / 2.f));
    window->draw(rect);
}

void RenderR3D::renderSprite(SMath::vec2 pos, int texture_id, int context, fv::context cont, SMath::vec2f size, SMath::vec2 screenSize)
{
    sf::Vector2u texSize = getTextureByIndex(texture_id)->getSize();

    sf::Sprite sprite;
    // cout << "ha\n";
    sprite.setTexture(*getTextureByIndex(texture_id));
    // cout << size << "\n";
    sprite.setPosition(forSFML::toSFMLVector(pos * cont.scale + SMath::vec2((int)cont.offset.x, (int)cont.offset.y)));
    size *= screenSize.y;
    sprite.setScale(sf::Vector2f(size.x / texSize.x, size.y / texSize.y));

    window->draw(sprite);
}
