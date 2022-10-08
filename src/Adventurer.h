#ifndef ADVENTURER_H
#define ADVENTURER_H

#ifdef _WIN32
#include <SDL.h>

#elif __linux__
#include <SDL2/SDL.h>
#endif

#include "Point.h"

//#include "InputManager.h"
#include "Animation.h"

#include <string>
#include <fstream>

// Usage Examples at the bottom of the page


/// SetProperties("adventurer_sheet", 0, 13, 32, 32, 200);

class Adventurer
{

public:
    Adventurer();
    Adventurer(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    ~Adventurer();
    void SetProperties(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Draw();
    void Update(const int &mouesX, const int &mouseY);
    void Input();
    void WorldToScreen(float worldX, float worldY, int &screenX, int &screenY);
    void ScreenToWorld(int screenX, int screenY, float &worldX, float &worldY);
    void WorldToScreenMouse(float worldX, float worldY, int &screenX, int &screenY);
    void ReadEvent(SDL_Event *sdlEvent);
    // float Normalize(float x, float y);
    // float Magnitude(float x, float y);
    Point<float> Normalize(Point<float> start, Point<float> end);


public:

    float m_speed = 0.2f;


    Point<float> m_worldPos{100.0f, 100.0f};

    Point<int> m_screenPos{100,100};
    //TODO: m_center is not a great name because its not actually the center 
    //its more of the physical foot placement in the world
    Point<int> m_center = {(m_screenPos.x), (m_screenPos.y) };

    Point<float> m_direction;

    bool m_DirectControl = true;




    SDL_Event m_sdlEvent;
    // int evTest;
    Animation m_anime;



    std::ofstream oFile;




};

#endif


/////////////////////////////   HOW TO  /////////////////////////////
//  
//  Create object with either blank constructor or with the properties in the constructor:
//  -Adventurer adventurer();
//  -Adventurer adventurer("adventurer_sheet", 0, 13, 32, 32, 200);
//  --  The "adventurer_sheet" must come from a previously loaded TextureManger::GetInstance().Load("path/to/asset.png");
//  --  The Path and file extension will be automatically stripped after the asset is loaded into a std::map
//  --  So just enter the name of the textureID to load that asset into the object
//  
//
//  -   Update(const int &mouesX, const int &mouseY);
//      --The Update function needs to be pointed to the mouse (x,y) variable from the game class
//      --Passed by const &, it will update the mouse position for the Adventurer object every frame
//
//
//
//
//
//
//
