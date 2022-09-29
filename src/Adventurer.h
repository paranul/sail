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
    void Update(const int &mouesX, const int &mouseY);
    void Input();
    void WorldToScreen(float worldX, float worldY, int &screenX, int &screenY);
    void ScreenToWorld(int screenX, int screenY, float &worldX, float &worldY);
    void WorldToScreenMouse(float worldX, float worldY, int &screenX, int &screenY);


public:

    float m_speed = 0.3f;
    float m_worldX = 100.0f;
    float m_worldY = 100.0f;

    int m_screenX = 100;
    int m_screenY = 100;

    bool m_DirectControl = true;

    int moveToX;
    int moveToY;



    //Animation m_anime;

};

#endif