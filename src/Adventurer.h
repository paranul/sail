#ifndef ADVENTURER_H
#define ADVENTURER_H


#include <SDL.h>

#include "Game.h"
//#include "InputManager.h"
#include "Animation.h"

#include <string>



/// SetProperties("adventurer_sheet", 0, 13, 32, 32, 200);

class Adventurer
{

public:
    Adventurer(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    ~Adventurer(){}
    void Draw();
    void Update();
    void Input();


private:

    int m_x = 50;
    int m_y = 50;



    Animation m_anime;

};

#endif