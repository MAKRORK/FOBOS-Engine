
#pragma once
#include "Block.h"
#include <iostream>

class Wall : public Block
{
private:
    void init();
    sf::RectangleShape rect;

public:
    void render(sf::RenderWindow &window) override;
    Wall() : Block() { init(); }
    Wall(sf::Vector2f _pos) : Block(_pos)
    {
        init();
    }
};
