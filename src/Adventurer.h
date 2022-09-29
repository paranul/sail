#ifndef ADVENTURER_H
#define ADVENTURER_H


#include <SDL.h>

//#include "InputManager.h"
//#include "Animation.h"

#include <string>



/// SetProperties("adventurer_sheet", 0, 13, 32, 32, 200);

class Adventurer
{

public:
    Adventurer();
    Adventurer(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    ~Adventurer();
    void SetProperties();
    void Draw();
    void Update();
    void Input();


private:

    float m_worldX = 50;
    float m_worldY = 50;

    int m_screenX;
    int m_screenY;



    //Animation m_anime;

};

#endif