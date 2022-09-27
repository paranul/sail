
#include "Adventurer.h"


Adventurer::Adventurer(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip)
{
    m_anime.SetProperties(textureID, spriteRow, frameCount, spriteWidth, spriteHeight, animationSpeed);
}

void Adventurer::Draw()
{
    m_anime.Draw(m_x, m_y);
}