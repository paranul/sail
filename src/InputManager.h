

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
    void KeyDown();
    void KeyUp();



private:
    InputManager();
    ~InputManager() {}

    const Uint8* m_keystate = nullptr;
    //SDL_Event m_sdlEvent;

};