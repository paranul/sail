#include "Nyctimus.h"
#include "../Game.h"
#include "../InputManager.h"
#include "../TextureManager.h"
#include "../Shapes.h"

#include <iostream>
#include <vector>


Nyctimus::Nyctimus()
{
    std::cout << "Set properties with Nyctimus.SetProperties()!\n";
    

    m_worldPos.x = 700.0f;
    m_worldPos.y = 500.0f;

    m_armAnime.SetProperties("arm_walk",0,8,32,32,200);
    m_legAnime.SetProperties("leg_walk",0,8,32,32,200);
}

void Nyctimus::SetProperties(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip)
{

}

void Nyctimus::Update()
{
    m_armAnime.Update();
    m_legAnime.Update();
}


//Draw order bottom to top, bottom shows up first, top last
void Nyctimus::Draw()
{


    m_legAnime.Draw(m_worldPos.x, m_worldPos.y);

    //Frame number 1 and 5 are the frames that the whole character shifts down 1 pixel, so need to update that here
    if(m_legAnime.GetFrame() == 1 || m_legAnime.GetFrame() == 5)
    {
        TextureManager::GetInstance().DrawObject("half_leather_chest_front", (float)m_worldPos.x, (float)m_worldPos.y + 1);
        TextureManager::GetInstance().DrawObject("head",(float)m_worldPos.x, (float)m_worldPos.y+1);
    }

    else
    {
        TextureManager::GetInstance().DrawObject("half_leather_chest_front", (float)m_worldPos.x, (float)m_worldPos.y);

        TextureManager::GetInstance().DrawObject("head",(float)m_worldPos.x, (float)m_worldPos.y);
    }

    m_armAnime.Draw((float)m_worldPos.x, (float)m_worldPos.y);

 /*IMPORTANT!-->Draw Order

    //  #4legs
    //  #3 chest
    //  #2 arm in front
    //  #1 head

It is reversed, the first lines get drawn on the bottom the later lines get drawn first

    */
    
}