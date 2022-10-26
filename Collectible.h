#pragma once
#include "GameObject.h"
#include "SDL.h"
#include "Vector2.h"

class Collectible :
    public GameObject
{
public:
    Collectible(Texture* collectibleTexture, Vector2 pos, int numberOfFrames = 1);
    ~Collectible();

    void draw(SDL_Renderer* renderer) override;
    virtual void update(float deltaTime) override;

private:
    unsigned int numberOfFrames;

};

