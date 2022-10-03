
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
    m_anime.SetProperties(textureID, spriteRow, frameCount, spriteWidth, spriteHeight, animationSpeed);
    //m_anime.SetProperties("adventurer_sheet", 0, 8, 32, 32, 100);
}

void Adventurer::Update(const int &mouseX, const int &mouseY)
{
    //TODO: Calculate objects center based on provided image width and height (For actual center)
    //TODO: Step 2 ?? Add either arbitrary numbers to get physical foot centered position of object
    //TODO: But then every different sized object will need new arbitrary numbers
    //TODO: Or figure out some formula for the ratio of arbitrary numbers to add based on the full object image
    m_center.x = m_screenPos.x + 14;
    m_center.y = m_screenPos.y + 29;
    
    if(m_DirectControl)
    {

        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_D))
        {
            //1440 width
            //890 height ///turn the fOffset stuff off to disable camera centering
            Game::GetInstance().fOffsetX = this->m_worldPos.x - 800;
            Game::GetInstance().fOffsetY = this->m_worldPos.y - 400;
            m_worldPos.x += m_speed;
        }
        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_A))
        {
            Game::GetInstance().fOffsetX = this->m_worldPos.x - 800;
            Game::GetInstance().fOffsetY = this->m_worldPos.y - 400;
            m_worldPos.x -= m_speed;
        }
        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_S))
        {
            Game::GetInstance().fOffsetX = this->m_worldPos.x - 800;
            Game::GetInstance().fOffsetY = this->m_worldPos.y - 400;
            m_worldPos.y += m_speed;
        }
        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_W))
        {
            Game::GetInstance().fOffsetX = this->m_worldPos.x - 800;
            Game::GetInstance().fOffsetY = this->m_worldPos.y - 400;
            m_worldPos.y -= m_speed;
        }

        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_SPACE))
        {
            std::cout << "Space pressed\n";
        }

        WorldToScreen(m_worldPos.x, m_worldPos.y, m_screenPos.x, m_screenPos.y);



        
    }

    else if(!m_DirectControl)
    {


        // if(m_sdlEvent.button.button == SDL_BUTTON_LEFT)
        if(InputManager::GetInstance().ReadMouseDown())
        {

            //This is the exact X, Y of the actual image not the object center
            // m_worldPos.x = mouseX + Game::GetInstance().fOffsetX;
            // m_worldPos.y = mouseY + Game::GetInstance().fOffsetY;

            // This works
            // m_worldPos.x = (mouseX + Game::GetInstance().fOffsetX) - 14;
            // m_worldPos.y = (mouseY + Game::GetInstance().fOffsetY) - 29;

            //This is the generalized formula teleports player to mouse position
            m_worldPos.x = (mouseX + Game::GetInstance().fOffsetX) + (m_screenPos.x - m_center.x);
            m_worldPos.y = (mouseY + Game::GetInstance().fOffsetY) + (m_screenPos.y - m_center.y);



        }
        WorldToScreen(m_worldPos.x, m_worldPos.y, m_screenPos.x, m_screenPos.y);

    }


        //Animation Update //TODO:: What about if frozen? dead? 
        m_anime.Update();
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
    m_anime.Draw(m_screenPos.x, m_screenPos.y);
    //TextureManager::GetInstance().DrawFrame("adventurer_sheet", m_screenPos.x, m_screenPos.y, 32, 32, 0, 8);

    Shape::GetInstance().DrawPixel(m_center.x, m_center.y);

    if(!m_DirectControl)
    {

        Shape::GetInstance().DrawLine(m_center.x, m_center.y, Game::GetInstance().m_mouseX,Game::GetInstance().m_mouseY);
    }
    
}

void Adventurer::SetProperties(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip)
{
    m_anime.SetProperties(textureID, spriteRow, frameCount, spriteWidth, spriteHeight, animationSpeed); 
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