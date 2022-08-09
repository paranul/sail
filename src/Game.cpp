
#ifdef _WIN32
#include <SDL.h>

#elif __linux__
#include <SDL2/SDL.h>

#endif

#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include "./testSource/S_Draw.h" //Perhaps add to compiler -I include path? So you can swam them out easier when you want to test others



Game::Game()
    :
    m_window(NULL),
    m_renderer(NULL),
    m_Active(false)

{
    std::cout << "Game Object Constructed!\n";
}
// Game::~Game()
// {
//     // std::cout << "Game Object Destroyed!\n";

//     // #ifdef _WIN32
//     // system("Pause");

//     // #elif __linux__
//     // //TODO: Add linux compatible console pause..
//     // #endif
// }

Game& Game::GetInstance()
{
    static Game instance;
    return instance;
}

SDL_Renderer* Game::GetRenderer()
{
    return m_renderer;
}

bool Game::IsRunning()
{
    return m_Active;
}

void Game::Init()
{
    //SDL_Init() = required
    //if error SDL will return negative flag
    if( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    {
        printf( "SDL_Init() Failed! SDL_Error: %s\n", SDL_GetError() );
        return; 
    }

    if(TTF_Init() != 0)
    {
        printf("TTF_Init() FAILED, SDL_TTF_ERROR: %s\n", TTF_GetError());
    }



    m_windowWidth = 800;
    m_windowHeight = 600;


    // https://wiki.libsdl.org/SDL_CreateWindow
    m_window = SDL_CreateWindow( "SAIL engine", 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, 
                                m_windowWidth, 
                                m_windowHeight, 
                                SDL_WINDOW_RESIZABLE );

    

    if(m_window == NULL)
    {
        printf( "SDL_Window() Failed! SDL_Error: %s\n", SDL_GetError() );
        return;
    }

    //https://wiki.libsdl.org/SDL_CreateRenderer
    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED);

    if(m_renderer == NULL)
    {
        printf( "SDL_Renderer() Failed! SDL_Error: %s\n", SDL_GetError() );
        return;
    }
    

    m_Active = true;

}

void Game::Setup()
{

    //POINTER::S_Draw::GetInstance()->Load("spear", "../assets/spear.png");
    POINTER::S_Draw::GetInstance()->LoadID("../assets/spear.png");
    POINTER::S_Draw::GetInstance()->LoadID("../assets/adventurer_sheet.png");

    text.m_font = TTF_OpenFont("../assets/Minecraft.ttf", 20);
    text.LoadFromRenderedText("Testing with writing...testing 1 2 3 4 5 6 7 \none two three four  five six seven how far is tTHIS thing going to go off screen"); 
    text.LoadFromRenderedText("This \t is \n another  \n line \n of text"); 

    const char* path;
    path = SDL_GetBasePath();

    std::cout << "Path of executable: "  << path << std::endl;

}

void Game::Run()
{

    Setup();

    while( m_Active )
    {
        ProcessInput();
        //start frametime timepoint here
        Update();
        //end frametime timepoint here
        Render();
        //subtract to see the time one  frame took
        
    }

}


static bool mouseButtonHeld = false;

void Game::ProcessInput()
{

    SDL_Event sdlEvent;

    while( SDL_PollEvent( &sdlEvent ) )
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
            {
                m_Active = false;
                break;
            }
            //Why its not catching this?
            case SDL_WINDOW_MAXIMIZED:
            {
                printf("MAXIMIZED!!!\n");
                SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
                printf("Window Width: %d\n", m_windowWidth);
                printf("Window Height: %d\n", m_windowHeight);
            }break;
            case SDL_KEYDOWN:
            {
                if(sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    m_Active = false;
                    //break;
                }
                if(sdlEvent.key.keysym.sym == SDLK_RIGHT)
                {
                    printf("KEY RIGHT\n");
                    POINTER::S_Draw::GetInstance()->m_offsetX += 10;
                    //break;
                }
                if(sdlEvent.key.keysym.sym == SDLK_LEFT)
                {
                    printf("KEY LEFT\n");
                    POINTER::S_Draw::GetInstance()->m_offsetX -= 10;
                    //break;
                }
                if(sdlEvent.key.keysym.sym == SDLK_DOWN)
                {
                    printf("KEY DOWN\n");
                    POINTER::S_Draw::GetInstance()->m_offsetY += 10;
                    //break;
                }
                if(sdlEvent.key.keysym.sym == SDLK_UP)
                {
                    printf("KEY UP\n");
                    POINTER::S_Draw::GetInstance()->m_offsetY -= 10;
                    //break;
                }
                if(sdlEvent.key.keysym.sym == SDLK_F1)
                {
                    static bool debugMode = false;
                    debugMode = !debugMode;
                    printf("Debug mode:%i \n", debugMode);
                }
                break;

            }
            
            case SDL_MOUSEWHEEL:
                if(sdlEvent.wheel.y > 0)
                {
                   // printf("Mouse wheel going up!\n");
                    POINTER::S_Draw::GetInstance()->m_scale += .5;
                    std::cout << POINTER::S_Draw::GetInstance()->m_scale << std::endl;
                    break;
                }
                else if(sdlEvent.wheel.y < 0)
                {
                    //printf("Mouse wheel down!\n");
                    POINTER::S_Draw::GetInstance()->m_scale -= .5;
                    std::cout << POINTER::S_Draw::GetInstance()->m_scale << std::endl;
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                if(sdlEvent.button.button == SDL_BUTTON_MIDDLE)
                {
                    printf("Middle mouse pressed\n");
                    printf("Middle Mouse Button Held!\n");
                    mouseButtonHeld = true;
                }
            default:
                {
                    //POINTER::S_Draw::GetInstance()->m_scale += 0;
                    //printf("Default case Running\n");
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(sdlEvent.button.button == SDL_BUTTON_MIDDLE)
                {
                    printf("Middle mouse released!\n");
                    mouseButtonHeld = false;

                }
                break;

            case SDL_MOUSEMOTION:
                {
                    //int x;
                    //int y;
                    //std::cout << sdlEvent.motion.x << "\n";
                    //std::cout << sdlEvent.motion.y << "\n";

                    //printf("Mouse: (%i,%i)\n", sdlEvent.motion.x, sdlEvent.motion.y);
                    //std::cout << sd
                }

        }
    }
}

void Game::Update()
{



}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
    SDL_RenderClear(m_renderer);

    TestTile tile1;

    tile1.DrawUknownTile();



    POINTER::S_Draw::GetInstance()->DrawQueriedTexture("spear", 500, 100);
    POINTER::S_Draw::GetInstance()->DrawQueriedTexture("adventurer_sheet", 0, 0);

    static int x =0;
    static int y = 0;



    text.Render(100,10);


    SDL_RenderPresent(m_renderer);
}

void Game::Kill()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

