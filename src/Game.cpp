
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
//#include <sstream>




#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
//////  INCLUDE THIS ONLY ONCE  /////
#define NK_IMPLEMENTATION       /////
////////////////////////////////////
#define NK_SDL_RENDERER_IMPLEMENTATION

#include "nuklear.h"
#include "nuklear_sdl_renderer.h"
#include "style.c"




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
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED );

    

    if(m_window == NULL)
    {
        printf( "SDL_Window() Failed! SDL_Error: %s\n", SDL_GetError() );
        return;
    }

    //https://wiki.libsdl.org/SDL_CreateRenderer
    //m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );

    if(m_renderer == NULL)
    {
        printf( "SDL_Renderer() Failed! SDL_Error: %s\n", SDL_GetError() );
        return;
    }



    //----------------------------------Nuklear GUI setup---------------------------


    m_nukCtxt = nk_sdl_init(m_window, m_renderer);

    {
        struct nk_font_atlas *atlas;
        struct nk_font_config config = nk_font_config(0);
        struct nk_font *font;

        nk_sdl_font_stash_begin(&atlas);
        font = nk_font_atlas_add_default(atlas, 13 * m_nukFontScale, &config);


        nk_sdl_font_stash_end();

        font->handle.height /= m_nukFontScale;

        nk_style_set_font(m_nukCtxt, &font->handle);
    }


    //m_nukBG.r = 0.10f, m_nukBG.g = 0.18f, m_nukBG.b = 0.24f, m_nukBG.a = 1.0f;

    //set_style(m_nukCtxt, THEME_DARK);


    m_Active = true;

}

void Game::Setup()
{

    //POINTER::S_Draw::GetInstance()->Load("spear", "../assets/spear.png");
    POINTER::S_Draw::GetInstance()->LoadID("../assets/spear.png");
    POINTER::S_Draw::GetInstance()->LoadID("../assets/oot-2d-map.png");
    TextureManager::GetInstance().Load("../assets/tree_0.png");
    TextureManager::GetInstance().Load("../assets/adventurer_sheet.png");

    adv.SetProperties("adventurer_sheet", 0, 13, 200);

    text.LoadFont("../assets/arial.ttf", 12);
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
        Input();
        //start frametime timepoint here
        Update();
        //end frametime timepoint here
        //subtract to see the time one  frame took
        Render();
        
    }

}




void Game::Input()
{
    //pretty important to have SDL_PumpEvents before you get the state to make sure you get the correct state (Key state and mouse state)
    SDL_PumpEvents();
    SDL_Event sdlEvent;
    buttons = SDL_GetMouseState(&mouseX, &mouseY);

    //SDL_GetKeyboardState(int * num);
    nk_input_begin(m_nukCtxt);
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
                    //printf("KEY RIGHT\n");
                    POINTER::S_Draw::GetInstance()->m_offsetX += 10;
                    //break;
                }
                if(sdlEvent.key.keysym.sym == SDLK_LEFT)
                {
                    //printf("KEY LEFT\n");
                    POINTER::S_Draw::GetInstance()->m_offsetX -= 10;
                    //break;
                }
                if(sdlEvent.key.keysym.sym == SDLK_DOWN)
                {
                    //printf("KEY DOWN\n");
                    POINTER::S_Draw::GetInstance()->m_offsetY += 10;
                    //break;
                }
                if(sdlEvent.key.keysym.sym == SDLK_UP)
                {
                    //printf("KEY UP\n");
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
        nk_sdl_handle_event(&sdlEvent);
    }
    nk_input_end(m_nukCtxt);



    if((buttons & SDL_BUTTON_MMASK) != 0)
    {

        Uint32 now = SDL_GetTicks();

        if(now - startMouseTime >= 1000)
        {

            //printf("MouseButton HELDDDDD\n");
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
    SDL_GetWindowSize(m_window, &m_windowWidth, &m_windowHeight);
    
    // currentTime = SDL_GetTicks();

    // //Do whats in this statement once a second
    // if(currentTime > lastTime + 1000)
    // {
    //     printf("Printing Update() report once per second...\n");
    //     // std::cout << "\tTime Elapsed: " << SDL_GetTicks() << "(ms)\n";
    //     // std::cout << "\tTime Elapsed: " << SDL_GetTicks() / 1000 << "(seconds)\n";
    //     // std::cout << "\tNumber of Update() Frames: " << countedUpdateFrames << "\n";
    //     // std::cout << "\t FPS: " << avgFPS << "\n";
    //     // //std::cout << "\t FPS: " << countedUpdateFrames / (SDL_GetTicks() / 1000) << "\n";
    //     // std::cout << "\tMiddle Mouse held: " << mouseButtonHeld << "\n";
    //     // lastTime = currentTime;
    // }

    adv.Update();


    // if(SDL_GetTicks() % 1000 == 0)
    // {

        
    // }
    
}

void Game::Render()
{
    // double avgFPS = double(countedUpdateFrames) / (SDL_GetTicks() / 1000);
    // currentTime = SDL_GetTicks();
    // if(currentTime > lastTime + 1000)
    // {
    //     printf("Printing Render() report once per second...\n");
    //     std::cout << "\t FPS: " << avgFPS << "\n";
    //     std::cout << "\tTime Elapsed: " << SDL_GetTicks() << "(ms)\n";
    //     std::cout << "\tTime Elapsed: " << SDL_GetTicks() / 1000 << "(seconds)\n";
    //     std::cout << "\tNumber of Render() Frames: " << countedUpdateFrames << "\n";
    //     lastTime = currentTime;
    // }


    SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
    SDL_RenderClear(m_renderer);

    TestTile tile1;
    //unicode 
    //РУСКИЙ

   // SDL_RenderGeometry()

    //tile1.DrawUknownTile();



    POINTER::S_Draw::GetInstance()->DrawQueriedTexture("spear", 500, 100);
    POINTER::S_Draw::GetInstance()->DrawQueriedTexture("oot-2d-map", -500, -800);



    static float rotation = 0.0f;
    
    const SDL_Point p = {0,0};


    TextureManager::GetInstance().DrawRotatingObject("tree_0", 500, 500, rotation, NULL);

    TextureManager::GetInstance().DrawObjectDimensions("adventurer_sheet", 300,200,25,40);


    adv.Draw(0,0, 32,30);
    

    // timeText.str("");
    // timeText << "milliseconds since start time " << SDL_GetTicks();
    // text.LoadFromRenderedText(timeText.str().c_str());
    // text.Render(0,0);

    text.LoadFromRenderedText("ANOTHER TEXT");
    text.Render(200,100, nullptr,-.9);

    text.LoadFromRenderedText("MOARRR TEXT");
    text.Render(200,200);




    //VLAD::::::The start of a nuklear window
    if(nk_begin(m_nukCtxt, "TITLE", nk_rect(0, 300, 300, 250),NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE | NK_WINDOW_CLOSABLE ))
            {
                nk_layout_row_static(m_nukCtxt, 30, 80, 2);
                //nk_layout_row_dynamic(m_nukCtxt, 3, 2);
                nk_label(m_nukCtxt, "WTFFFFFF\n\n\n\n\n", NK_TEXT_LEFT);
                //nk_layout_row_static(m_nukCtxt, 30, 30, 2);
                nk_layout_row_dynamic(m_nukCtxt, 8, 1);
                nk_value_int(m_nukCtxt, "SDL_GetTicks", SDL_GetTicks());
                nk_layout_row_dynamic(m_nukCtxt, 8, 2);
                nk_value_int(m_nukCtxt, "Window Width", m_windowWidth);
                nk_value_int(m_nukCtxt, "Window Height", m_windowHeight);
                nk_layout_row_dynamic(m_nukCtxt, 8, 1);
                nk_value_float(m_nukCtxt, "Zoom Scale", POINTER::S_Draw::GetInstance()->m_scale);
                nk_value_int(m_nukCtxt, "TextureManager map_size()", TextureManager::GetInstance().m_textureMap.size());
                
            }


    //VLAD::::::Must include this after every window
    //NOTE:: might fail to read info after nk_end()
    nk_end(m_nukCtxt);

    if (nk_begin(m_nukCtxt, "Demo", nk_rect(50, 50, 230, 250),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            enum {EASY, HARD};
            static int op = EASY;
            static int property = 20;

            nk_layout_row_static(m_nukCtxt, 30, 80, 2);
            if (nk_button_label(m_nukCtxt, "novsynv"))
            {
                fprintf(stdout, "button pressed\n");
                printf("BUTTON PRESSED\n");
                printf("Easy label: %i", op);
                printf("property value: %i", property);
            }
            nk_layout_row_dynamic(m_nukCtxt, 30, 2);

            
            nk_label(m_nukCtxt, "TEST: TEXT LABEL\n", NK_TEXT_LEFT);


            
            //if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
            //if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(m_nukCtxt, 25, 1);
            //nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

            nk_layout_row_dynamic(m_nukCtxt, 20, 1);
            nk_label(m_nukCtxt, "background:", NK_TEXT_LEFT);
            nk_layout_row_dynamic(m_nukCtxt, 25, 1);
            if (nk_combo_begin_color(m_nukCtxt, nk_rgb_cf(m_nukBG), nk_vec2(nk_widget_width(m_nukCtxt),400))) {
                nk_layout_row_dynamic(m_nukCtxt, 120, 1);
                m_nukBG = nk_color_picker(m_nukCtxt, m_nukBG, NK_RGBA);
                nk_layout_row_dynamic(m_nukCtxt, 25, 1);
                m_nukBG.r = nk_propertyf(m_nukCtxt, "#R:", 0, m_nukBG.r, 1.0f, 0.01f,0.005f);
                m_nukBG.g = nk_propertyf(m_nukCtxt, "#G:", 0, m_nukBG.g, 1.0f, 0.01f,0.005f);
                m_nukBG.b = nk_propertyf(m_nukCtxt, "#B:", 0, m_nukBG.b, 1.0f, 0.01f,0.005f);
                m_nukBG.a = nk_propertyf(m_nukCtxt, "#A:", 0, m_nukBG.a, 1.0f, 0.01f,0.005f);
                nk_combo_end(m_nukCtxt);
            }
        }
        nk_end(m_nukCtxt);

    countedUpdateFrames++;
    rotation += 0.01;

    nk_sdl_render(NK_ANTI_ALIASING_OFF);
    SDL_RenderPresent(m_renderer);

}

void Game::Kill()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

