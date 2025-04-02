#include "AnimatedTexture.h"

std::vector<AnimatedTexture *> AnimatedTexture::animatedTextures;

void AnimatedTexture::start()
{
    played = true;
}

void AnimatedTexture::restart()
{
    current = 0;
    to_next = delta;
}

void AnimatedTexture::stop()
{
    played = false;
}

int AnimatedTexture::getID()
{
    return textures[current];
}

void AnimatedTexture::updateAll(float _delta)
{
    for (AnimatedTexture *anim : animatedTextures)
    {
        anim->update(_delta);
    }
}

void AnimatedTexture::update(float _delta)
{
    if (!played)
        return;
    to_next -= _delta;
    if (to_next <= 0)
    {
        to_next += delta;
        if (!loop && current == countOfFrames - 1)
        {
            stop();
            return;
        }
        current = (current + 1) % countOfFrames;
    }
}

void AnimatedTexture::setCountOfFrames(int _fr)

{
    countOfFrames = _fr;
    textures = new int[_fr];
}

void AnimatedTexture::setFrame(int frame_id, int id)
{
    textures[frame_id] = id;
}

void AnimatedTexture::setFrameByName(int frame_id, std::string _name)
{
    textures[frame_id] = Render::getTextureIndexByName(_name);
}

void AnimatedTexture::setFramesFromTileset(std::string name)
{
    SMath::vec2 h = Render::getTexturesFromTileSet(name);
    if (textures)
        delete textures;
    countOfFrames = h.y - h.x;
    textures = new int[countOfFrames];
    for (int i = 0; i < countOfFrames; i++)
    {
        textures[i] = i + h.x;
    }
}

void AnimatedTexture::setLoop(bool _loop)
{
    loop = _loop;
}
