
#include "Animation.h"

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
}

void Animation::Draw(int x, int y, int spriteWidth, int spriteHeight)
{
    
}