#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#ifdef _WIN32
#include <SDL.h>

#elif __linux__
#include <SDL2/SDL.h>
#endif


class InputManager
{

public:
    //InputManager(); //Constructor should be Private for static singleton classes
    static InputManager& GetInstance();
    void Listen();

    bool ReadKeyDown(SDL_Scancode key);
    //Super testing and probably done incorretlly only reads Left mouse button for now
    bool ReadMouseDown();
    bool MiddleMouseHeld();
    void KeyDown();
    void KeyUp();



private:
    InputManager();
    ~InputManager() {}

    const Uint8* m_keystate = nullptr;
    Uint32 m_buttonState = 0;

    int m_mouseX;
    int m_mouseY;
    //SDL_Event m_sdlEvent;


    //////////////Mouse Test Code//////////////
    Uint32 startMouseTime;
    bool m_middleButtonHeld = false;
    bool m_mousePosCaptured = false;
    int m_mouseStartX;
    int m_mouseStartY;

};

#endif