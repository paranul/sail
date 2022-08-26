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

class Game
{

public:

    static Game& GetInstance();

    void Init(); //SDL Initializations
    void Setup(); //Game specific Setups
    void Run();

    void ProcessInput();
    void Update();
    void Render();

    SDL_Renderer* GetRenderer();
    bool IsRunning();


    void Kill();

public:
    int m_windowWidth;
    int m_windowHeight;
    Uint32 buttons;
    int mouseX;
    int mouseY;
    inline static bool mouseButtonHeld = false;
    Uint32 startMouseTime;

    



private:
    Game();
    ~Game() {}


SDL_Window* m_window;
SDL_Renderer* m_renderer;

bool m_Active;

FTexture text;

};

#endif