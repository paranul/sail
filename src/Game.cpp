
#ifdef _WIN32
#include <SDL.h>

#elif __linux__
#include <SDL2/SDL.h>

#endif

#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include "./testSource/S_Draw.h" //Perhaps add to compiler -I include path? So you can swap them out easier when you want to test others
#include "Shapes.h"
#include "TextureManager.h"




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
    POINTER::S_Draw::GetInstance()->LoadID("../assets/oot-2d-map.png");
    TextureManager::GetInstance().Load("../assets/tree_0.png");
    TextureManager::GetInstance().Load("../assets/adventurer_sheet.png");

    text.LoadFont("../assets/Minecraft.ttf", 20);
    text.LoadFromRenderedText("Testing with writing...testing 1 2 3 4 5 6 7 \none two three four  five six seven how far is tTHIS thing going to go off screen"); 
    //text.LoadFromRenderedText("This \t is \n another  \n line \n of text"); 

    //This is important for later to make sure that we are finding the assets and data folder correctly, even if exe is not in /bin
    const char* path;
    path = SDL_GetBasePath();

    std::cout << "Path of executable: "  << path << std::endl;
    for(int i = 0; i < 10; i++)
    {
        std::cout << path[i];
    }

    //SDL_VERSION()
    SDL_version linked;
    SDL_GetVersion(&linked);
    //accessing twice at the same time makes this crash
    //https://docs.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=msvc-170
    //printf("\nSDL Version: %o", linked.major);
    //adding a + before a number will print it as a number otherwise cout tries to print as character
    //https://stackoverflow.com/questions/19562103/uint8-t-cant-be-printed-with-cout
    std::cout << "\nSDL Version cout<<: " << +linked.major << "." << linked.minor + 0 <<"." << +linked.patch << "\n";

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
        //subtract to see the time one  frame took
        Render();
        
    }

}




void Game::ProcessInput()
{
    //pretty important to have SDL_PumpEvents before you get the state to make sure you get the correct state (Key state and mouse state)
    SDL_PumpEvents();
    SDL_Event sdlEvent;
    buttons = SDL_GetMouseState(&mouseX, &mouseY);

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

                    std::cout << "Middle Mouse held: "<<mouseButtonHeld << "\n";
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
                    
                    startMouseTime = SDL_GetTicks();

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



    if((buttons & SDL_BUTTON_MMASK) != 0)
    {

        Uint32 now = SDL_GetTicks();

        if(now - startMouseTime >= 1000)
        {

            printf("MouseButton HELDDDDD\n");
            mouseButtonHeld = true;
        }
        //State machine tags this on release as well
        //small fix for now is to check if middle mouse is released and tag it as released...not sure if good fix

    }

    //If i pump events I should not need this check every single frame....
    // else if((buttons & SDL_BUTTON_MMASK) == 0)
    // {
    //     mouseButtonHeld = false;
    // }



}

void Game::Update()
{



}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
    SDL_RenderClear(m_renderer);

    TestTile tile1;
    //unicode 
    //РУСКИЙ

   // SDL_RenderGeometry()

    //tile1.DrawUknownTile();



    POINTER::S_Draw::GetInstance()->DrawQueriedTexture("spear", 500, 100);
    POINTER::S_Draw::GetInstance()->DrawQueriedTexture("oot-2d-map", 0, 0);

    const SDL_Point p = {0,0};

    TextureManager::GetInstance().DrawRotatingObject("tree_0", 500, 500, 300, &p);

    TextureManager::GetInstance().DrawObjectDimensions("adventurer_sheet", 300,200,25,40);



    text.Render(200,100, nullptr,-5.0);


    SDL_RenderPresent(m_renderer);
}

void Game::Kill()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

