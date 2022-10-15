
#include "Animation.h"
#include "TextureManager.h"
#include <iostream>



void Animation::SetProperties(std::string textureID, int spriteRow, int frameCount ,int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip)
{
    m_textureID = textureID;
    m_spriteRow = spriteRow;
    m_frameCount = frameCount;
    m_animationSpeed = animationSpeed;
    m_spriteWidth = spriteWidth;
    m_spriteHeight = spriteHeight;
    m_flip = flip;
}



//TODO:: Need to add protections so this is not used without proper setup
//WARNING: SDL_GetTicks() continues to run even if the application is "Paused"
//making it unsuitable for some specific game logic which requires a start / stop timer
void Animation::Update()
{

    m_spriteFrame = (SDL_GetTicks() / m_animationSpeed) % m_frameCount;


    //SDL_GetTicks() / # of milliseconds == a timer for that amount of milliseconds.
    //std::cout << SDL_GetTicks() / 500 << '\n'; // will be incrementing every 500 miliseconds
    //std::cout << SDL_GetTicks() / 1000 << '\n'; // will be incrementing every 1 second
}


//TODO:: Need to add protections so this is not used without proper setup
void Animation::Draw(int x, int y, int spriteWidth, int spriteHeight)
{

    TextureManager::GetInstance().DrawFrame(m_textureID, x, y, spriteWidth, spriteHeight, m_spriteRow, m_spriteFrame, m_flip);

}

void Animation::Draw(int x, int y)
{
    TextureManager::GetInstance().DrawFrame(m_textureID, x, y, m_spriteWidth, m_spriteHeight, m_spriteRow, m_spriteFrame, m_flip);
}

void Animation::Draw(float x, float y)
{
    TextureManager::GetInstance().DrawFrame(m_textureID, x, y, m_spriteWidth, m_spriteHeight, m_spriteRow, m_spriteFrame, m_flip);
}


const int Animation::GetFrame()
{
    return m_spriteFrame;
}