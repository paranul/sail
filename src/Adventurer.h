#ifndef ADVENTURER_H
#define ADVENTURER_H

#ifdef _WIN32
#include <SDL.h>

#elif __linux__
#include <SDL2/SDL.h>
#endif

#include "Point.h"

//#include "InputManager.h"
#include "Animation.h"

#include <string>



/// SetProperties("adventurer_sheet", 0, 13, 32, 32, 200);

class Adventurer
{

public:
    Adventurer();
    Adventurer(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    ~Adventurer();
    void SetProperties(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Draw();
    void Update(const int &mouesX, const int &mouseY);
    void Input();
    void WorldToScreen(float worldX, float worldY, int &screenX, int &screenY);
    void ScreenToWorld(int screenX, int screenY, float &worldX, float &worldY);
    void WorldToScreenMouse(float worldX, float worldY, int &screenX, int &screenY);
    void ReadEvent(SDL_Event *sdlEvent);


public:

    float m_speed = 0.3f;


    Point<float> m_worldPos{100.0f, 100.0f};

    Point<int> m_screenPos{100,100};
    //TODO: m_center is not a great name because its not actually the center 
    //its more of the physical foot placement in the world
    Point<int> m_center = {(m_screenPos.x), (m_screenPos.y) };



    // int m_screenX = 100;
    // int m_screenY = 100;

    bool m_DirectControl = false;




    SDL_Event m_sdlEvent;
    // int evTest;
    Animation m_anime;

};

#endif