
#include "Animation.h"
#include "TextureManager.h"
#include <iostream>

Animation::Animation()
{

}

void Animation::SetProperties(std::string textureID, int spriteRow, int frameCount, int animationSpeed, SDL_RendererFlip flip)
{
    m_textureID = textureID;
    m_spriteRow = spriteRow;
    m_frameCount = frameCount;
    m_animationSpeed = animationSpeed;
    m_flip = flip;
}


void Animation::Update()
{
    m_spriteFrame = (SDL_GetTicks() / m_animationSpeed) % m_frameCount;

    //SDL_GetTicks() / # of milliseconds == a timer for that amount of milliseconds.
    //std::cout << SDL_GetTicks() / 500 << '\n'; // will be incrementing every 500 miliseconds
    //std::cout << SDL_GetTicks() / 1000 << '\n'; // will be incrementing every 1 second
}

void Animation::Draw(int x, int y, int spriteWidth, int spriteHeight)
{
    TextureManager::GetInstance().DrawFrame(m_textureID, x, y, spriteWidth, spriteHeight, m_spriteRow, m_spriteFrame, m_flip);
}