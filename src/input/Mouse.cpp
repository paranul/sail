
#include "Mouse.h"

#include "SDL.h"

#include <algorithm>

int Mouse::x = 0;
int Mouse::xLast = 0;
int Mouse::y = 0;
int Mouse::yLast = 0;

std::array<bool, Mouse::ButtonCount> Mouse::buttons {false};
std::array<bool, Mouse::ButtonCount> Mouse::buttonsDown {false};
std::array<bool, Mouse::ButtonCount> Mouse::buttonsUp {false};




void Mouse::Initialize()
{

    std::fill(buttons.begin(), buttons.end(), false);

    std::fill(buttonsDown.begin(), buttonsDown.end(), false);
    std::fill(buttonsUp.begin(), buttonsUp.end(), false);
}



void Mouse::Update()
{
    std::fill(buttonsDown.begin(), buttonsDown.end(), false);
    std::fill(buttonsUp.begin(), buttonsUp.end(), false);

    uint32_t state = SDL_GetMouseState(&x, &y);

    for(int i = 0; i < ButtonCount; i++)
    {
        //
        bool wasDown = buttons[i];
        buttons[i] = state & SDL_BUTTON(i + 1);
        bool isDown = buttons[i];

        if(wasDown && !isDown)
        {
            buttonsUp[i] = true;
        }
        else if(!wasDown && isDown)
        {
            buttonsDown[i] = true;
        }
    }
}

bool Mouse::ButtonDown(int button)
{
    //assert(button >= 0 && button < buttonCount)
    if(button >= 0 && button <= Mouse::ButtonCount)
    {
        return buttons[button];
    }

    return false;
}

bool Mouse::ButtonUp(int button)
{
    //assert(button >= 0 && button < buttonCount)

    return false;
}