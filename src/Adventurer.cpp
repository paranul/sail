
#include "Adventurer.h"
#include "Game.h"
#include "InputManager.h"
#include "TextureManager.h"

#include <iostream>

Adventurer::Adventurer()
{
    std::cout << "Adventurer Properties not set! Use Adventurer.SetProperties() \n";
}

Adventurer::Adventurer(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip)
{
    //m_anime.SetProperties(textureID, spriteRow, frameCount, spriteWidth, spriteHeight, animationSpeed);
}

void Adventurer::Update()
{
    if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_D))
    {
        m_worldX += 1;
    }
    if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_A))
    {
        m_worldX -= 1;
    }
    if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_S))
    {
        m_worldY += 1;
    }
    if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_W))
    {
        m_worldY -= 1;
    }
    

}

void Adventurer::Draw()
{
    //m_anime.Draw(m_x, m_y);
    TextureManager::GetInstance().DrawObject("tree_0", m_worldX, m_worldY);
}

void Adventurer::SetProperties()
{

}

Adventurer::~Adventurer()
{

}