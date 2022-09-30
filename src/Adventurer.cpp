
#include "Adventurer.h"
#include "Game.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "Shapes.h"

#include <iostream>




Adventurer::Adventurer()
{
    std::cout << "Adventurer Properties not set! Use Adventurer.SetProperties() \n";
}

Adventurer::Adventurer(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip)
{
    //m_anime.SetProperties(textureID, spriteRow, frameCount, spriteWidth, spriteHeight, animationSpeed);
}

void Adventurer::Update(const int &mouseX, const int &mouseY)
{

    
    if(m_DirectControl)
    {

        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_D))
        {
            //1440 width
            //890 height ///turn the fOffset stuff off to disable camera centering
            Game::GetInstance().fOffsetX = this->m_worldX - 800;
            Game::GetInstance().fOffsetY = this->m_worldY - 400;
            m_worldX += m_speed;
        }
        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_A))
        {
            Game::GetInstance().fOffsetX = this->m_worldX - 800;
            Game::GetInstance().fOffsetY = this->m_worldY - 400;
            m_worldX -= m_speed;
        }
        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_S))
        {
            Game::GetInstance().fOffsetX = this->m_worldX - 800;
            Game::GetInstance().fOffsetY = this->m_worldY - 400;
            m_worldY += m_speed;
        }
        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_W))
        {
            Game::GetInstance().fOffsetX = this->m_worldX - 800;
            Game::GetInstance().fOffsetY = this->m_worldY - 400;
            m_worldY -= m_speed;
        }

        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_SPACE))
        {
            std::cout << "Space pressed\n";
        }

        WorldToScreen(m_worldX, m_worldY, m_screenX, m_screenY);
        
    }

    else if(!m_DirectControl)
    {


        // if(m_sdlEvent.button.button == SDL_BUTTON_LEFT)
        if(InputManager::GetInstance().ReadMouseDown())
        {
            m_worldX = mouseX + Game::GetInstance().fOffsetX;
            m_worldY = mouseY + Game::GetInstance().fOffsetY;




        }
        WorldToScreen(m_worldX, m_worldY, m_screenX, m_screenY);

    }
}

void Adventurer::ReadEvent(SDL_Event *sdlEvent)
{
    m_sdlEvent = *sdlEvent;
    if(m_sdlEvent.button.button == SDL_BUTTON_RIGHT)
    {
        printf("HELLO FROM ADVENTUERE\n");
    }
    if(m_sdlEvent.button.button == SDL_BUTTON_LEFT)
    {
        printf("HELLO FROM ADVENTUEREWITH THE LEFT\n");
    }
}


void Adventurer::Draw()
{
    //m_anime.Draw(m_x, m_y);
    TextureManager::GetInstance().DrawObjectDimensions("adventurer_sheet", m_screenX, m_screenY, 32, 32);

    if(!m_DirectControl)
    {

        Shape::GetInstance().DrawLine(m_screenX, m_screenY, Game::GetInstance().m_mouseX,Game::GetInstance().m_mouseY);
    }
    
}

void Adventurer::SetProperties()
{

}

void Adventurer::WorldToScreen(float worldX, float worldY, int &screenX, int &screenY)
{
    screenX = (int)(worldX - Game::GetInstance().fOffsetX);
    screenY = (int)(worldY - Game::GetInstance().fOffsetY);
}

void Adventurer::ScreenToWorld(int screenX, int screenY, float &worldX, float &worldY)
{
    worldX = (float)(screenX + Game::GetInstance().fOffsetX);
    worldY = (float)(screenY + Game::GetInstance().fOffsetY);
}

void Adventurer::WorldToScreenMouse(float worldX, float worldY, int &screenX, int &screenY)
{
    screenX = (int)(Game::GetInstance().fOffsetX - worldX);
    screenY = (int)(Game::GetInstance().fOffsetY - worldY);
}

Adventurer::~Adventurer()
{

}