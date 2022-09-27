
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
void Animation::Update()
{
        if(m_textureID != "NULL")
        {
            m_spriteFrame = (SDL_GetTicks() / m_animationSpeed) % m_frameCount;
        }
    else
    {
        std::cout << "\tERROR: Update Not Running\n";
    }

    //SDL_GetTicks() / # of milliseconds == a timer for that amount of milliseconds.
    //std::cout << SDL_GetTicks() / 500 << '\n'; // will be incrementing every 500 miliseconds
    //std::cout << SDL_GetTicks() / 1000 << '\n'; // will be incrementing every 1 second
}


//TODO:: Need to add protections so this is not used without proper setup
void Animation::Draw(int x, int y, int spriteWidth, int spriteHeight)
{
    if(m_textureID != "NULL")
    {
        TextureManager::GetInstance().DrawFrame(m_textureID, x, y, spriteWidth, spriteHeight, m_spriteRow, m_spriteFrame, m_flip);
    }
    else
    {
        std::cout << "\tERROR: textureID Not set\n";
    }
}

void Animation::Draw(int x, int y)
{
    TextureManager::GetInstance().DrawFrame(m_textureID, x, y, m_spriteWidth, m_spriteHeight, m_spriteRow, m_spriteFrame, m_flip);
}