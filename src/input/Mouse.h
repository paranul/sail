
#pragma once

#include <array>

class Mouse
{

public:

    static void Update();
    inline static int X() {return x;}
    inline static int Y() {return y;}

    static void Initialize();

    static bool Button(int button);
    static bool ButtonDown(int button);
    static bool ButtonUp(int button);


private:

// SDL Supports up to 5 mouse buttons, see SDL_BUTTON_LEFT e.t.c
    constexpr static const int ButtonCount = 5;

    static int x, xLast;
    static int y, yLast;

    static std::array<bool, ButtonCount> buttons;
    static std::array<bool, ButtonCount> buttonsDown;
    static std::array<bool, ButtonCount> buttonsUp;
};

enum
{

//Just an identifier at where mouse buttons start being counted 
    SAIL_INPUT_MOUSE_FIRST = 1,

    SAIL_INPUT_MOUSE_LEFT = SAIL_INPUT_MOUSE_FIRST,
    SAIL_INPUT_MOUSE_MIDDLE = 2,
    SAIL_INPUT_MOUSE_RIGHT = 3,
    SAIL_INPUT_MOUSE_X1 = 4,
    SAIL_INPUT_MOUSE_X2 = 5,

    SAIL_INPUT_MOUSE_LAST = 5

};