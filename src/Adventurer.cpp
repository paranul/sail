
#include "Adventurer.h"
#include "Game.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "Shapes.h"

#include <iostream>
#include <vector>

#include <math.h>





Adventurer::Adventurer()
{
    std::cout << "Adventurer Properties not set! Use Adventurer.SetProperties() \n";


    //Test respawn at same location;

    std::ifstream file;
    file.open("../assets/testData.txt");

    std::string contents;

    std::vector<std::string> v_contents;

    //this will only read the first line
    // if(file.is_open())
    // {
    //     file >> s;

    //     std::cout  << "file Contents: "<< s;
    // }

    if(file.is_open())
    {
        while(file.good())
        {
            file >> contents;
            v_contents.push_back(contents);
            //std::cout  << "file Contents: "<< contents << '\n';
        }
    }

    for(auto& i : v_contents)
    {
        std::cout  << "v_contents: "<< i << '\n';
    }

    m_worldPos.x = std::stof(v_contents[0]);
    m_worldPos.y = std::stof(v_contents[1]);

    // for(int i = 0; i < v_contents.size(); i++)
    // {
    //     m_worldPos.x = std::stof(v_contents[i]);

    // }
    




    /////   C style needs work (aka no idea what im doing wrong)  /////

    //oFile.open("../assets/testData.txt");

    //std::ifstream file("../assets/testData.txt");
    // FILE* fp = fopen("../assets/testData.txt", "r");
    // if( fp = NULL)
    // {
    //     printf("File reading (\"../assets/testData.txt\") failed\n");
    // }

    // char buf[100];
    // while(fscanf(fp, "%*s %*s %*s ", buf) == 1)
    // {
    //     printf("%s\n", buf);
    // }


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

    m_direction = Normalize(Point<float>((float)m_center.x, float(m_center.y)), Point<float>(mouseX, mouseY));
    
    if(m_DirectControl)
    {

        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_D))
        {
            //1440 width
            //890 height ///turn the fOffset stuff off to disable camera centering
            m_anime.SetProperties("adventurer_sheet", 1, 8, 32, 32, 100);
            Game::GetInstance().fOffsetX = this->m_worldPos.x - 800;
            Game::GetInstance().fOffsetY = this->m_worldPos.y - 400;
            m_worldPos.x += m_speed;
        }
        if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_A))
        {
            m_anime.SetProperties("adventurer_sheet", 1, 8, 32, 32, 100,SDL_FLIP_HORIZONTAL);
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

    }

        //TODO: Reset animation to idle
        //  ------For now this is just a hacky way to do this without much effort (Wait 1 sec and set property to idle)
    //m_anime.SetProperties("adventurer_sheet", 0, 13, 32, 32, 100);

    uint32_t currentTime = SDL_GetTicks();
    static uint32_t lastTime = 0;

    //Do whats in this statement once a second
    if(currentTime > lastTime + 1000)
    {
        m_anime.SetProperties("adventurer_sheet", 0, 13, 32, 32, 100);

        lastTime = currentTime;
    }



        //Wether in direct control or mouse input control, and future controller control, need to Keep updating this
        WorldToScreen(m_worldPos.x, m_worldPos.y, m_screenPos.x, m_screenPos.y);
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
        //normalize
        float magnitude;
        float X = (float)Game::GetInstance().m_mouseX - (float)m_center.x;
        float Y = (float)Game::GetInstance().m_mouseY - (float)m_center.y;

        float uX;
        float uY;


        magnitude = sqrt((X * X) + (Y * Y));

        uX = (X / magnitude);
        uY = (Y / magnitude);




        Shape::GetInstance().DrawLine(m_center.x, m_center.y, Game::GetInstance().m_mouseX,Game::GetInstance().m_mouseY);
    }
    
}



// float Adventurer::Magnitude(float x, float y)
// {

// }

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
    oFile.open("../assets/testData.txt");

    oFile << m_worldPos.x << '\n';
    oFile << m_worldPos.y;
}

Point<float> Adventurer::Normalize(Point<float> start, Point<float> end)
{
    Point<float> begin;
    float magnitude;
    Point<float> unitVector;

    begin.x = float(end.x - start.x);
    begin.y = float(end.y - start.y);

    magnitude = sqrt((begin.x * begin.x) + (begin.y * begin.y));

    unitVector.x = (begin.x / magnitude);
    unitVector.y = (begin.y / magnitude);

    return unitVector;
}