#ifndef ANIMATION_H
#define ANIMATION_H


#ifdef _WIN32
#include <SDL.h>

#elif __linux__
#include<SDL2/SDL.h>
#endif

#include <string>



class Animation
{

public:
    Animation() {}
    //std::string textureID needs to already have been loaded from TextureManager()
    void SetProperties(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    //m_animationSpeed # will dictate how many milliseconds per frame
    void Update();
    void Draw(int x, int y, int spriteWidth, int spriteHeight);
    void Draw(int x, int y);

private:
    std::string m_textureID = "NULL";
    int m_spriteRow;
    int m_frameCount;
    int m_animationSpeed;
    int m_spriteWidth;
    int m_spriteHeight;
    SDL_RendererFlip m_flip;
    int m_spriteFrame;
    


};

#endif