
#include "Shapes.h"
#include "Game.h"
#include "../external/glm/glm.hpp"

Shape& Shape::GetInstance()
{
    static Shape instance;

    return instance;
}


void Shape::DrawRect(int x, int y, int width, int height)
{
    SDL_Rect rect = {x, y, width, height};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255,0,0,255);
    SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &rect);
}

void Shape::DrawPixel(int x, int y)
{
    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255,0,0,255);
    SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(),x, y);
}


void Shape::DrawCircle(int centerX, int centerY, int radius)
{
    int LeftX = centerX - radius;
    int topY = centerY - radius;
    int rightX = centerX + radius;
    int bottomY = centerY + radius;

    Shape::GetInstance().DrawPixel(LeftX, topY);
    Shape::GetInstance().DrawPixel(rightX, topY);
    Shape::GetInstance().DrawPixel(rightX, bottomY);
    Shape::GetInstance().DrawPixel(LeftX, bottomY);
}