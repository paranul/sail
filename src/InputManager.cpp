



#include "Game.h"
#include "InputManager.h"

#include <iostream>

InputManager::InputManager()
{
    m_keystate = SDL_GetKeyboardState(nullptr);
    Listen();
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
    //m_buttonState = SDL_GetMouseState(&m_mouseX, &m_mouseX);

    if((m_buttonState & SDL_BUTTON_LMASK) != 0)
    {
        return true;
    }

    return false;

}

bool InputManager::MiddleMouseHeld()
{

    m_buttonState = SDL_GetMouseState(&m_mouseX, &m_mouseX);

    startMouseTime = SDL_GetTicks();

    if((m_buttonState & SDL_BUTTON_MMASK) != 0)
    {

        Uint32 now = SDL_GetTicks();

        if(now - startMouseTime >= 100)
        {
            m_middleButtonHeld = true;
            
            if(m_middleButtonHeld)
            {   

                if(m_mousePosCaptured == false)
                {
                    m_mouseStartX = m_mouseX;
                    m_mouseStartY = m_mouseY;

                    m_mousePosCaptured = true;
                    std::cout << m_mouseStartX;

                }


                    m_mouseStartX = m_mouseX;
                    m_mouseStartY = m_mouseY;

                    return true;


            }
            
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
            }


        }

    }
}