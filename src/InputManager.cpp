



#include "Game.h"
#include "InputManager.h"

#include <iostream>

InputManager::InputManager()
{
    m_keystate = SDL_GetKeyboardState(nullptr);
}

InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}


bool InputManager::ReadKeyDown(SDL_Scancode key)
{
    return (m_keystate[key]);
}

bool InputManager::ReadMouseDown()
{
    m_buttonState = SDL_GetMouseState(&m_mouseX, &m_mouseX);

    if((m_buttonState & SDL_BUTTON_LMASK) != 0)
    {
        return true;
    }

    return false;

}
        //TODO: Timer Function not popping off correctly because it goes out of scope and 
        //  therefore never has a chance to be compared properly.. think of fix
bool InputManager::MiddleMouseHeld()
{       

    m_buttonState = SDL_GetMouseState(&m_mouseX, &m_mouseX);

    startMouseTime = SDL_GetTicks();

    if((m_buttonState & SDL_BUTTON_MMASK) != 0)
    {
        
        //std::cout << "INPUT MANAGER middle mouse pressed\n";

        Uint32 now = SDL_GetTicks();

        //TODO: Timer Function not popping off correctly because it goes out of scope and 
        //  therefore never has a chance to be compared properly.. think of fix

        //if(now - startMouseTime >= 100)
        {
            m_middleButtonHeld = true;
            
            return true;
        }

    }



    return false;
}

void InputManager::KeyDown()
{
    m_keystate = SDL_GetKeyboardState(nullptr);
}

void InputManager::KeyUp()
{
    m_keystate = SDL_GetKeyboardState(nullptr);
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
            case SDL_MOUSEBUTTONDOWN:
            {

            }break;
            case SDL_MOUSEBUTTONUP:
            {
                m_middleButtonHeld = false;
                printf("Middle mouse released!\n");
            }

            


        }

    }
}