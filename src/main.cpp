// #ifdef _WIN32
// #include <SDL.h>
// #include <SDL_image.h>
// #include <SDL_ttf.h>
// #include <SDL_mixer.h>

// #elif __linux__
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
// #endif

#include "../external/glm/vec2.hpp"

#include "ECS/ECS.h"


#include <iostream>

#include "Game.h"



int main(int argc, char* argv[])
{


    //void __debugbreak();

    Game::GetInstance().Init();

    Game::GetInstance().Setup();

    while(Game::GetInstance().IsRunning())
    {
        Game::GetInstance().ProcessInput();
        Game::GetInstance().Update();
        Game::GetInstance().Render();
    }




    return 0;
}