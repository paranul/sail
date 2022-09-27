



#include "Game.h"
#include "InputManager.h"

InputManager::InputManager()
{
    m_keystate = SDL_GetKeyboardState(nullptr);
}

InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

void InputManager::KeyDown()
{
    m_keystate = SDL_GetKeyboardState(nullptr);
}

void InputManager::KeyUp()
{
    m_keystate = SDL_GetKeyboardState(nullptr);
}

bool InputManager::ReadKeyDown(SDL_Scancode key)
{
    return (m_keystate[key]);
}

void InputManager::Listen()
{

    SDL_Event sdlEvent;

    while( SDL_PollEvent(&sdlEvent))
    {
        switch(sdlEvent.type)
        {
            case SDL_QUIT:
            {
                Game::GetInstance().Kill();
            }break;

            case SDL_KEYDOWN:
            {
                KeyDown();
            }break;

            case SDL_KEYUP:
            {
                KeyUp();
            }break;


        }

    }
}