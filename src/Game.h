#ifndef GAME_H
#define GAME_H

#ifdef _WIN32
#include <SDL.h>
#include "./testSource/FTexture.h"

#elif __linux__
#include <SDL2/SDL.h>
#include "./testSource/FTexture.h"
#endif

#include "./testSource/Tile.h"
//#include "Animation.h"
#include "Adventurer.h"
#include "./testSource/Nyctimus.h"

#include <sstream>


#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
//#define NK_IMPLEMENTATION
#define NK_SDL_RENDERER_IMPLEMENTATION

#include "nuklear.h"

class Game
{

public:

    static Game& GetInstance();

    void Init(); //SDL Initializations
    void Setup(); //Game specific Setups
    void Run();

    void Input();
    void Update();
    void Render();

    SDL_Renderer* GetRenderer();
    bool IsRunning();

    void WorldToScreen(float worldX, float worldY, int &screenX, int &screenY);

    Point<float> Normalize(Point<float> start, Point<float> end);

    //generate floats between [-1.0f, 1.0f]
    float negRNG();



    void Kill();

public:
//NOTE: Make these into static singletons?? I Will probably need to access them all over the place
    int m_windowWidth;
    int m_windowHeight;

    //SDL_Mouse stuff
    Uint32 buttons;
    int m_mouseX;
    int m_mouseY;
    int m_mouseXoffset = 0;
    int m_mouseYoffset = 0;
    int m_mouseHeldStartX;
    int m_mouseHeldStartY;
    inline static bool m_mouseButtonHeld = false;
    inline static bool m_mousePOScaptured = false;
    Uint32 startMouseTime;

    float fOffsetX = 0.0f;
    float fOffsetY = 0.0f;


    //SDL_Timer report stuff
    unsigned int lastTime = 0;
    unsigned int currentTime;
    int countedUpdateFrames = 0;



private:
    Game();
    ~Game() {}


    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    bool m_Active;

    SDL_Event sdlEvent;

    FTexture text;



    Uint32 startTime = 0;
    std::stringstream timeText;

    // Animation adv;
    Adventurer adveturer;
    Adventurer adventurer2;




    ////test stuff////

    int c_worldx = 50;
    int c_worldy = 50;
    int c_screenx = 50;
    int c_screeny = 50;


    int c2_worldx = 10;
    int c2_worldy = 10;
    int c2_screenx = 10;
    int c2_screeny = 10;

    int map_worldx = 0;
    int map_worldy = 0;
    int map_screenx = 0;
    int map_screeny = 0;


    

    

    




    Nyctimus nyc;


    //---------------------------------Nuklear GUI components---------------------------------//
    struct nk_context *m_nukCtxt;
    struct nk_colorf m_nukBG;

    float m_nukFontScale = 1;

};

#endif