#pragma once
#include "Texture.h"
#include <vector>

class AnimatedTexture : public Texture
{
private:
    int *textures;
    float delta = 0.1f;
    int countOfFrames = 0;
    static std::vector<AnimatedTexture *> animatedTextures;
    float to_next = 0.1f;
    int current = 0;
    bool played = true;
    bool loop = true;

public:
    AnimatedTexture() { animatedTextures.push_back(this); }
    AnimatedTexture(int _fr)
    {
        animatedTextures.push_back(this);
        countOfFrames = _fr;
        textures = new int[_fr];
    }
    void start();
    void restart();
    void stop();

    int getID() override;

    static void updateAll(float _delta);
    void update(float _delta);

    void setCountOfFrames(int _fr);
    int getountOfFrames() { return countOfFrames; }

    void setFrame(int frame_id, int id);
    void setFrameByName(int frame_id, std::string _name);
    void setFramesFromTileset(std::string name);

    void setDelta(float _delta)
    {
        delta = _delta;
        to_next = _delta;
    }
    float getDelta() { return delta; }

    int getCurrent() { return current; }

    void setLoop(bool _loop);
    bool getLoop() { return loop; }
};
