
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
#include "InputManager.h"
//#include <sstream>

#include <math.h>
#include <random>




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
    //adveturer("adventurer_sheet", 0, 13, 32, 32, 200)

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
    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    //m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );

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

    srand(time(NULL));

    ///rng test float [0 , 1]
    // for(int i = 0; i < 10; i++)
    // {
    //     std::cout << static_cast<float> ( rand() ) / static_cast<float>(RAND_MAX) << "\n";
    // }

    const float min = -1.0f;
    const float max = 1.0f;


    std::random_device rand_dev;

    std::mt19937  generator(rand_dev());

    std::uniform_real_distribution<float> dist(min, max);
    for(int i = 0; i < 1; i++)
    {
        std::cout << dist(generator) << "\n";
    }




    ////Nyc item stuff////
    TextureManager::GetInstance().Load("../assets/head.png");
    TextureManager::GetInstance().Load("../assets/half_leather_chest_front.png");
    TextureManager::GetInstance().Load("../assets/leg_walk.png");
    TextureManager::GetInstance().Load("../assets/arm_walk.png");


    //POINTER::S_Draw::GetInstance()->Load("spear", "../assets/spear.png");
    POINTER::S_Draw::GetInstance()->LoadID("../assets/spear.png");
    POINTER::S_Draw::GetInstance()->LoadID("../assets/oot-2d-map.png");
    TextureManager::GetInstance().Load("../assets/tree_0.png");
    TextureManager::GetInstance().Load("../assets/adventurer_sheet.png");

    POINTER::S_Draw::GetInstance()->LoadID("../assets/light3.png");


    adveturer.SetProperties("adventurer_sheet", 0, 13, 32, 32,100);

    adveturer.SetControl(true);

    adventurer2.SetProperties("adventurer_sheet", 0, 13, 32, 32,100);
    adventurer2.m_worldPos.x += 100.0f;
    adventurer2.m_worldPos.y += 100.0f;

    text.LoadFont("../assets/arial.ttf", 12);
    text.LoadFromRenderedText("Testing with writing...testing 1 2 3 4 5 6 7 \none two three four  five six seven how far is tTHIS thing going to go off screen"); 
    //text.LoadFromRenderedText("This \t is \n another  \n line \n of text"); 

    //This is important for later to make sure that we are finding the assets and data folder correctly, even if exe is not in /bin
    char* path;
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
    
    buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);

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

                }
                break;

            }
            
            case SDL_MOUSEWHEEL:
                if(sdlEvent.wheel.y > 0)
                {
                   // printf("Mouse wheel going up!\n");
                    POINTER::S_Draw::GetInstance()->m_scale += .1;
                    std::cout << POINTER::S_Draw::GetInstance()->m_scale << std::endl;
                    break;
                }
                else if(sdlEvent.wheel.y < 0)
                {
                    //printf("Mouse wheel down!\n");
                    POINTER::S_Draw::GetInstance()->m_scale -= .1;
                    std::cout << POINTER::S_Draw::GetInstance()->m_scale << std::endl;
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                SDL_PumpEvents();
                adveturer.ReadEvent(&sdlEvent);

                if(sdlEvent.button.button == SDL_BUTTON_MIDDLE)
                {
                    printf("Middle mouse pressed\n");
                    startMouseTime = SDL_GetTicks();
                    m_mouseHeldStartX = m_mouseX;
                    m_mouseHeldStartY = m_mouseY;

                }
            // default:
            //     {
            //         //POINTER::S_Draw::GetInstance()->m_scale += 0;
            //         //printf("Default case Running\n");
            //     }
            //     break;
            // case SDL_MOUSEBUTTONUP:
            //     if(sdlEvent.button.button == SDL_BUTTON_MIDDLE)
            //     {
            //         // printf("Middle mouse released!\n");
            //         //m_mouseButtonHeld = false;
            //         m_mousePOScaptured = false;
            //         //SDL_SetRelativeMouseMode(SDL_FALSE);


            //     }
            //     break;

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



    if(InputManager::GetInstance().MiddleMouseHeld())
    {

        fOffsetX -= (m_mouseX - m_mouseHeldStartX);
        fOffsetY -= (m_mouseY - m_mouseHeldStartY);

        m_mouseHeldStartX = m_mouseX;
        m_mouseHeldStartY = m_mouseY;
    }



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

    //adv.Update();


    // if(SDL_GetTicks() % 1000 == 0)
    // {

        
    // }



    nyc.Update();

    adveturer.Update(m_mouseX, m_mouseY);



    adventurer2.Update(m_mouseX, m_mouseY);

    WorldToScreen(float(c_worldx), float(c_worldy), c_screenx, c_screeny);
    WorldToScreen(float(c2_worldx), float(c2_worldy), c2_screenx, c2_screeny);

    WorldToScreen(map_worldx, map_worldy, map_screenx, map_screeny);

    //c2_worldx +=1;
    
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

    //TestTile tile1;
    //unicode 
    //РУСКИЙ

    //SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_MUL);




    //SDL_SetTextureBlendMode(POINTER::S_Draw::GetInstance()->GetTexture("oot-2d-map"), SDL_BLENDMODE_NONE);
    //SDL_SetTextureColorMod(POINTER::S_Draw::GetInstance()->GetTexture("oot-2d-map"), red, blue, green);

    POINTER::S_Draw::GetInstance()->DrawQueriedTexture("spear", 500, 100);
    POINTER::S_Draw::GetInstance()->DrawQueriedTexture("oot-2d-map", map_screenx, map_screeny);



    static float rotation = 0.0f;
    
    const SDL_Point p = {0,0};


    TextureManager::GetInstance().DrawRotatingObject("tree_0", 500, 500, rotation, NULL);

    TextureManager::GetInstance().DrawObjectDimensions("adventurer_sheet", 300,200,25,40);

    Shape::GetInstance().DrawCircle(c_screenx, c_screeny, 20);

    Shape::GetInstance().DrawRect(c2_screenx, c2_screeny, 20,20);


    //adv.Draw(50,50);
    adveturer.Draw();


    adventurer2.Draw();

    nyc.Draw();




    //SDL_SetRenderTarget(m_renderer, )

    //SDL_SetTextureAlphaMod(POINTER::S_Draw::GetInstance()->GetTexture("light3"), 0);
    //SDL_SetTextureBlendMode(POINTER::S_Draw::GetInstance()->GetTexture("light3"), SDL_BLENDMODE_MUL);
    //SDL_SetTextureAlphaMod()

    //POINTER::S_Draw::GetInstance()->DrawQueriedTexture("light3", 100, 100);

    // timeText.str("");
    // timeText << "milliseconds since start time " << SDL_GetTicks();
    // text.LoadFromRenderedText(timeText.str().c_str());
    // text.Render(0,0);

    text.LoadFromRenderedText("ANOTHER TEXT");
    text.Render(200,100, nullptr,-.9);

    text.LoadFromRenderedText("MOARRR TEXT");
    text.Render(200,200);



    struct nk_rect nkrct = {0, 0, 300, 450};

    //VLAD::::::The start of a nuklear window
    if(nk_begin(m_nukCtxt, "Adventurer Properties", nkrct,NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE | NK_WINDOW_CLOSABLE ))
            {
                nk_layout_row_static(m_nukCtxt, 30, 80, 2);
                //nk_layout_row_dynamic(m_nukCtxt, 3, 2);
                nk_label(m_nukCtxt, "nk_Rect Dimensions", NK_TEXT_LEFT);
                nk_value_int(m_nukCtxt, "Width", nkrct.w);
                nk_value_int(m_nukCtxt, "Height", nkrct.h);
                //nk_layout_row_static(m_nukCtxt, 30, 30, 2);
                nk_layout_row_dynamic(m_nukCtxt, 8, 1);
                nk_value_int(m_nukCtxt, "SDL_GetTicks", SDL_GetTicks());
                nk_layout_row_dynamic(m_nukCtxt, 8, 2);
                nk_value_int(m_nukCtxt, "Window Width", m_windowWidth);
                nk_value_int(m_nukCtxt, "Window Height", m_windowHeight);
                nk_layout_row_dynamic(m_nukCtxt, 8, 1);
                nk_value_float(m_nukCtxt, "Zoom Scale", POINTER::S_Draw::GetInstance()->m_scale);
                //NOTE: Need to put texturemanager class back to private member variables eventuallu...
                nk_value_int(m_nukCtxt, "TextureManager map_size()", TextureManager::GetInstance().m_textureMap.size());
                nk_value_int(m_nukCtxt, "Middle Mouse Held", m_mouseButtonHeld);
                nk_layout_row_static(m_nukCtxt, 30, 140, 2);
                nk_value_int(m_nukCtxt, "Mouse_Screen X", m_mouseX);
                nk_value_int(m_nukCtxt, "Y", m_mouseY);
                nk_layout_row_dynamic(m_nukCtxt, 8, 1);
                nk_value_int(m_nukCtxt, "S_DRAW offsetX", POINTER::S_Draw::GetInstance()->m_offsetX);
                nk_value_int(m_nukCtxt, "fOffsetX", fOffsetX);   
                nk_value_int(m_nukCtxt, "fOffsetY", fOffsetY);
                nk_value_int(m_nukCtxt, "mouseState", buttons);  
                nk_value_int(m_nukCtxt, "Adventurer centerX", adveturer.m_center.x);
                nk_value_int(m_nukCtxt, "Adventurer centerY", adveturer.m_center.y);
                nk_value_int(m_nukCtxt, "Adventurer screenX", adveturer.m_screenPos.x);       
                nk_value_int(m_nukCtxt, "Adventurer screenY", adveturer.m_screenPos.y);  
                nk_value_float(m_nukCtxt, "Adventurer WorldX", adveturer.m_worldPos.x);
                nk_value_float(m_nukCtxt, "Adventurer WorldY", adveturer.m_worldPos.y);
                nk_value_float(m_nukCtxt, "Adventurer last Y", adveturer.m_lastPosition.y);
                nk_value_float(m_nukCtxt, "X", adveturer.m_lastPosition.x);
                nk_layout_row_static(m_nukCtxt, 30, 80, 1);
                if(nk_button_label(m_nukCtxt, "Direct Control"))
                {
                    adveturer.m_DirectControl = !adveturer.m_DirectControl;
                }
                nk_layout_row_static(m_nukCtxt, 30, 200, 2);
                nk_value_float(m_nukCtxt, "adventurer direction X", adveturer.m_direction.x);
                nk_value_float(m_nukCtxt, "Y", adveturer.m_direction.y);
                nk_value_bool(m_nukCtxt,"m_moving", adveturer.m_moving);
                // nk_layout_row_static(m_nukCtxt, 30, 200, 2);
                // nk_value_float(m_nukCtxt, "Character Vector X", characterVector.x);
                // nk_value_float(m_nukCtxt, "Y", characterVector.y);
                // nk_layout_row_static(m_nukCtxt, 30, 100, 2);
                // nk_value_float(m_nukCtxt, "magnitude", magnitude);
                // nk_layout_row_static(m_nukCtxt, 30, 200, 2);
                // nk_value_float(m_nukCtxt, "unitVector X", unitVector.x);
                // nk_value_float(m_nukCtxt, "Y", unitVector.y);




                //nk_widget(nk_rect(0.0f,0.0f,100.0f,100.0f), m_nukCtxt);


                // nk_value_int(m_nukCtxt, "adventurer Event", adveturer.evTest);   


            }


    //VLAD::::::Must include this after every window
    //NOTE:: might fail to read info after nk_end()
    nk_end(m_nukCtxt);

    // if (nk_begin(m_nukCtxt, "Demo", nk_rect(50, 50, 230, 250),
    //         NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
    //         NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    //     {
    //         enum {EASY, HARD};
    //         static int op = EASY;
    //         static int property = 20;

    //         nk_layout_row_static(m_nukCtxt, 30, 80, 2);
    //         if (nk_button_label(m_nukCtxt, "novsynv"))
    //         {
    //             fprintf(stdout, "button pressed\n");
    //             printf("BUTTON PRESSED\n");
    //             printf("Easy label: %i", op);
    //             printf("property value: %i", property);
    //         }
    //         nk_layout_row_dynamic(m_nukCtxt, 30, 2);

            
    //         nk_label(m_nukCtxt, "TEST: TEXT LABEL\n", NK_TEXT_LEFT);


            
    //         //if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
    //         //if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
    //         nk_layout_row_dynamic(m_nukCtxt, 25, 1);
    //         //nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

    //         nk_layout_row_dynamic(m_nukCtxt, 20, 1);
    //         nk_label(m_nukCtxt, "background:", NK_TEXT_LEFT);
    //         nk_layout_row_dynamic(m_nukCtxt, 25, 1);
    //         if (nk_combo_begin_color(m_nukCtxt, nk_rgb_cf(m_nukBG), nk_vec2(nk_widget_width(m_nukCtxt),400))) {
    //             nk_layout_row_dynamic(m_nukCtxt, 120, 1);
    //             m_nukBG = nk_color_picker(m_nukCtxt, m_nukBG, NK_RGBA);
    //             nk_layout_row_dynamic(m_nukCtxt, 25, 1);
    //             m_nukBG.r = nk_propertyf(m_nukCtxt, "#R:", 0, m_nukBG.r, 1.0f, 0.01f,0.005f);
    //             m_nukBG.g = nk_propertyf(m_nukCtxt, "#G:", 0, m_nukBG.g, 1.0f, 0.01f,0.005f);
    //             m_nukBG.b = nk_propertyf(m_nukCtxt, "#B:", 0, m_nukBG.b, 1.0f, 0.01f,0.005f);
    //             m_nukBG.a = nk_propertyf(m_nukCtxt, "#A:", 0, m_nukBG.a, 1.0f, 0.01f,0.005f);
    //             nk_combo_end(m_nukCtxt);
    //         }
    //     }
    //     nk_end(m_nukCtxt);

    countedUpdateFrames++;
    rotation += 0.01f;

    nk_sdl_render(NK_ANTI_ALIASING_OFF);
    SDL_RenderPresent(m_renderer);

}



void Game::Kill()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


void Game::WorldToScreen(float worldX, float worldY, int &screenX, int &screenY)
{
    screenX = (int)(worldX - fOffsetX);
    screenY = (int)(worldY - fOffsetY);
}

Point<float> Game::Normalize(Point<float> start, Point<float> end)
{
    Point<float> begin;
    float magnitude;
    Point<float> unitVector;

    begin.x = float(m_mouseX - start.x);
    begin.y = float(m_mouseY - start.y);

    magnitude = sqrt((begin.x * begin.x) + (begin.y * begin.y));

    unitVector.x = (begin.x / magnitude);
    unitVector.y = (begin.y / magnitude);

    return unitVector;

}

float Game::negRNG()
{

    srand(time(NULL));

    float LO = -1.0f;
    float HI = 1.0f;

    return (( (LO + static_cast<float> (rand()) ) / static_cast<float>(RAND_MAX / (HI-LO) ) ) - 0.5f );

    // for(int i = 0; i < 10; i++)
    // {
    //     std::cout << ( (LO + static_cast<float> ( rand() ) ) / static_cast<float>(RAND_MAX / (HI-LO)) )  - 0.5f<< "\n";
    // }

}