
#include "Adventurer.h"
#include "Game.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "Shapes.h"

#include <iostream>
#include <vector>

#include <math.h>
#include<random>




Adventurer::Adventurer()
{
    std::cout << "Adventurer Properties not set! Use Adventurer.SetProperties() \n";


    //Test respawn at same location;

    // std::ifstream file;
    // file.open("../assets/testData.txt");

    // std::string contents;

    // std::vector<std::string> v_contents;

    // //this will only read the first line
    // // if(file.is_open())
    // // {
    // //     file >> s;

    // //     std::cout  << "file Contents: "<< s;
    // // }

    // if(file.is_open())
    // {
    //     while(file.good())
    //     {
    //         file >> contents;
    //         v_contents.push_back(contents);
    //         //std::cout  << "file Contents: "<< contents << '\n';
    //     }
    // }

    // for(auto& i : v_contents)
    // {
    //     std::cout  << "v_contents: "<< i << '\n';
    // }

    // m_worldPos.x = std::stof(v_contents[0]);
    // m_worldPos.y = std::stof(v_contents[1]);

    // // for(int i = 0; i < v_contents.size(); i++)
    // // {
    // //     m_worldPos.x = std::stof(v_contents[i]);

    // // }
    




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

    m_lastPosition = m_worldPos;


    //TODO: Calculate objects center based on provided image width and height (For actual center)
    //TODO: Step 2 ?? Add either arbitrary numbers to get physical foot centered position of object
    //TODO: But then every different sized object will need new arbitrary numbers
    //TODO: Or figure out some formula for the ratio of arbitrary numbers to add based on the full object image
    m_center.x = m_screenPos.x + 15;
    m_center.y = m_screenPos.y + 29;

    if(!m_Control)
    {
        DoRandomMovement();
    }
    
    else if(m_Control)
    {

        
        if(m_DirectControl)
        {

            if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_D))
            {
                //1440 width
                //890 height ///turn the fOffset stuff off to disable camera centering
                //m_anime.SetProperties("adventurer_sheet", 1, 8, 32, 32, 100);
                Game::GetInstance().fOffsetX = this->m_worldPos.x - 800;
                Game::GetInstance().fOffsetY = this->m_worldPos.y - 400;
                m_worldPos.x += m_speed;
                m_direction.x = 1.0f;

                //TODO: Check if the other movement keys are in the UP position as well here
                //If they are set m_direction.Y = 0
                //if not let them be added into the m_direction to get proper X=1.0 and Y=1.0 


            }
            if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_A))
            {
                //m_anime.SetProperties("adventurer_sheet", 1, 8, 32, 32, 100,SDL_FLIP_HORIZONTAL);
                Game::GetInstance().fOffsetX = this->m_worldPos.x - 800;
                Game::GetInstance().fOffsetY = this->m_worldPos.y - 400;
                m_worldPos.x -= m_speed;
                m_direction.x = -1.0f;


            }
            if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_S))
            {
                Game::GetInstance().fOffsetX = this->m_worldPos.x - 800;
                Game::GetInstance().fOffsetY = this->m_worldPos.y - 400;
                m_worldPos.y += m_speed;
                m_direction.y = 1.0f;


            }
            if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_W))
            {
                Game::GetInstance().fOffsetX = this->m_worldPos.x - 800;
                Game::GetInstance().fOffsetY = this->m_worldPos.y - 400;
                m_worldPos.y -= m_speed;
                m_direction.y = -1.0f;


            }

            if(InputManager::GetInstance().ReadKeyDown(SDL_SCANCODE_SPACE))
            {
                std::cout << "Space pressed\n";
            }
            
        }

        else if(!m_DirectControl)
        {
            //TODO: Should change this algorithm 
            //No need to normalize every frame (really unperformant), just need to take the vector between
            //mouse and player.center and clamp the x and y position of both to 10 or 20 or something
            //Nomarlization will still be important for diagonal movement consistency for speed 
            //but that can be normalized once and probably just cached somehow
            //TODO #2: Normalization is still not quite correct... should be 0 in one position if the other is 1.0
            //m_direction = Normalize( Point<float>((float)m_center.x, float(m_center.y)) , Point<float>(mouseX, mouseY) );

            // if(m_sdlEvent.button.button == SDL_BUTTON_LEFT)
            if(InputManager::GetInstance().ReadMouseDown())
            {
                m_direction = Normalize( Point<float>((float)m_center.x, float(m_center.y)) , Point<float>(mouseX, mouseY) );
                m_goToPosition.x = mouseX;
                m_goToPosition.y = mouseY;

                //This is the exact X, Y of the actual image not the object center
                // m_worldPos.x = mouseX + Game::GetInstance().fOffsetX;
                // m_worldPos.y = mouseY + Game::GetInstance().fOffsetY;

                // This works
                // m_worldPos.x = (mouseX + Game::GetInstance().fOffsetX) - 14;
                // m_worldPos.y = (mouseY + Game::GetInstance().fOffsetY) - 29;

                //This is the MAIN generalized formula teleports player to mouse position
                //m_worldPos.x = (mouseX + Game::GetInstance().fOffsetX) + (m_screenPos.x - m_center.x);
                //m_worldPos.y = (mouseY + Game::GetInstance().fOffsetY) + (m_screenPos.y - m_center.y);

                //This MAIN CODE works while mouse is held down
                // m_worldPos.x += (m_direction.x) * m_speed;
                // m_worldPos.y += (m_direction.y) * m_speed;






                ////TODO: Algorithm for mouse movement;
                /*
                1 - when left mouse is clicked save mouse coordinates 
                2 - update player m_worldPos.x & y += m_direction.x * speed untill 
                        m_worldPos.x & y are equal to saved mouse coordiantes
                */

            }

            //Theres a bug here, sometimes m_direction * speed is not properly matching the m_center == m_gotoposition
            //maybe not exactly but sometimes character doesnt stop running after he reaches his position
            //NOTE->Bug is fixed by using WithinRange() in the reset

                if(m_center != m_goToPosition)
                {
                    m_worldPos.x += (m_direction.x) * m_speed;
                    m_worldPos.y += (m_direction.y) * m_speed;

                }
                //reset m_direction
                if(WithinRange(m_center.x, m_goToPosition.x, 1) && WithinRange(m_center.y, m_goToPosition.y, 1))
                {
                    m_direction.x = 0.0f;
                    m_direction.y = 0.0f;
                }

        }

            //TODO: Reset animation to idle
            //  ------For now this is just a hacky way to do this without much effort (Wait 1 sec and set property to idle)
        //m_anime.SetProperties("adventurer_sheet", 0, 13, 32, 32, 100);

        // uint32_t currentTime = SDL_GetTicks();
        // static uint32_t lastTime = 0;

        //Do whats in this statement once a second
        // if(currentTime > lastTime + 1000)
        // {
        //     m_anime.SetProperties("adventurer_sheet", 0, 13, 32, 32, 100);

        //     lastTime = currentTime;
        // }





    }



    // m_direction.x = negRNG();
    // m_direction.y = negRNG();

    // m_worldPos.x += m_direction.x * m_speed;
    // m_worldPos.y += m_direction.y * m_speed;

    //Wether in direct control or mouse input control, and future controller control, need to Keep updating this
    WorldToScreen(m_worldPos.x, m_worldPos.y, m_screenPos.x, m_screenPos.y);

    //TODO: Warning youre comparing float values here, might need to do some sort of clamping or rounding function
    //In the future
    if(m_lastPosition != m_worldPos)
    {
        m_moving = true;
    }
    else
    {
        m_moving = false;
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
#ifdef debug
    //rect around full pictue shape
    Shape::GetInstance().DrawRect(m_screenPos.x, m_screenPos.y, 32, 32);
    //mark of world position on screen (0,0) of picture
    Shape::GetInstance().DrawMark(Point<int>{m_screenPos.x,m_screenPos.y}, 3,  SDL_Color{0,255,0});
    //Mark Center Position
    Shape::GetInstance().DrawMark(Point<int>{m_center.x, m_center.y}, 3, SDL_Color{255,255,0});
#endif

    if(m_goToPosition != m_center)
    {
        //Mark GoTo Position
        Shape::GetInstance().DrawCircle(m_goToPosition.x, m_goToPosition.y, 5);
        Shape::GetInstance().DrawMark(Point<int>{m_goToPosition.x, m_goToPosition.y}, 5, SDL_Color{0,100,255});
        //Shape::GetInstance().DrawPixel(int(m_goToPosition.x), int(m_goToPosition.y));
    }

    if(m_moving)
    {
        if(m_direction.x > 0)   m_anime.SetProperties("adventurer_sheet", 1, 8, 32, 32, 100);

        else if(m_direction.x < 0)    m_anime.SetProperties("adventurer_sheet", 1, 8, 32, 32, 100, SDL_FLIP_HORIZONTAL);

        else if(m_direction.y > 0)
        {
            m_anime.SetProperties("adventurer_sheet", 1, 8, 32, 32, 100);
        }
        else if(m_direction.y < 0)
        {
            m_anime.SetProperties("adventurer_sheet", 1, 8, 32, 32, 100);
        }
    }
    else
    {
        m_anime.SetProperties("adventurer_sheet", 0, 13, 32, 32, 100);
    }

    m_anime.Draw(m_screenPos.x, m_screenPos.y);
    //TextureManager::GetInstance().DrawFrame("adventurer_sheet", m_screenPos.x, m_screenPos.y, 32, 32, 0, 8);



    if(!m_DirectControl)
    {
        //Shape::GetInstance().DrawLine(float(m_center.x), float(m_center.y), float(m_center.x) + (m_direction.x)*10 ,float(m_center.y) + (m_direction.y)*10);

#ifdef debug
        //Draw Line to mouse cursor from center
        Shape::GetInstance().DrawLine(float(m_center.x), float(m_center.y), float(Game::GetInstance().m_mouseX) ,float(Game::GetInstance().m_mouseY));
#endif
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

    if(magnitude == 0.0f)
    {
        unitVector = Point<float>{0.0f,0.0f};

        return unitVector;
    }

    return unitVector;
}

void Adventurer::DoRandomMovement()
{

    currentTime = SDL_GetTicks();
    //lastTime = 0;

    ////    Do whats in this statement once n second
    if(currentTime > lastTime + 1000)
    {
        m_direction.x = rngPlus();
        m_direction.y = rngPlus();

        lastTime = currentTime;
    }



    m_worldPos.x += m_direction.x * m_speed;
    m_worldPos.y += m_direction.y * m_speed;
}

float Adventurer::negRNG()
{

    //srand(time(0));

    float LO = -1.0f;
    float HI = 1.0f;
    //std::cout << ( (LO + static_cast<float> ( rand() ) ) / static_cast<float>(RAND_MAX / (HI-LO)) )  - 0.5f<< "\n";
    return (( (LO + static_cast<float> (rand()) ) / static_cast<float>(RAND_MAX / (HI-LO) ) ) - 0.5f );

    // for(int i = 0; i < 10; i++)
    // {
    //     std::cout << ( (LO + static_cast<float> ( rand() ) ) / static_cast<float>(RAND_MAX / (HI-LO)) )  - 0.5f<< "\n";
    // }

}

float Adventurer::rngPlus()
{
    const float min = -1.0f;
    const float max = 1.0f;


    std::random_device rand_dev;

    std::mt19937  generator(rand_dev());

    std::uniform_real_distribution<float> dist(min, max);

    return (dist(generator));
    // for(int i = 0; i < 1; i++)
    // {
    //     std::cout << dist(generator) << "\n";
    // }
}

void Adventurer::SetPosition(float x, float y)
{
    m_worldPos.x = x;
    m_worldPos.y = y;
}

void Adventurer::SetControl(bool isOwned)
{
    m_Control = isOwned;
}

void Adventurer::SetSpeed(float speed)
{
    m_speed = speed;
}

bool Adventurer::WithinRange(float num1, float num2, float deviation)
{
    return (fabsf(num1 - num2) <= deviation);
}

bool Adventurer::WithinRange(int num1, int num2, int deviation)
{
    return (abs(num1 - num2) <= deviation);
}