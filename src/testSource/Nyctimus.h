#ifndef NYCTIMUS_H
#define NYCTIMUS_H

#ifdef _WIN32
#include <SDL.h>

#elif __linux__
#include <SDL2/SDL.h>
#endif

#include "../Point.h"

//#include "InputManager.h"
#include "../Animation.h"

class Nyctimus
{
public:

    Nyctimus();

    void Update();

    void Draw();

    void Input();

    void SetProperties(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);



private:

    float m_speed = 0.2f;
    Point<float> m_worldPos{100.0f, 100.0f};
    Point<int> m_screenPos{100,100};
    //TODO: m_center is not a great name because its not actually the center 
    //its more of the physical foot placement in the world
    Point<int> m_center = {(m_screenPos.x), (m_screenPos.y) };

    Animation m_legAnime;
    Animation m_armAnime;

};

#endif