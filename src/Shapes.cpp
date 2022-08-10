
#include "Shapes.h"
#include "Game.h"
#include "../external/glm/glm.hpp"
#include <cmath>



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

    Shape::GetInstance().DrawPixel(centerX, centerY);

    for(int x = LeftX; x <= rightX; x++)
    {
        
        for(int y = topY; y <= bottomY; y++)
        {
            int a = centerX - x;
            int b = centerY - y;

            if( sqrt((a*a) + (b*b)) == radius)
            {
                Shape::GetInstance().DrawPixel(x, y);
            }
        }

    }

}

void Shape::DrawCircleF(float centerX, float centerY, float radius)
{
    float LeftX = centerX - radius;
    float topY = centerY - radius;
    float rightX = centerX + radius;
    float bottomY = centerY + radius;

    // Shape::GetInstance().DrawPixel(LeftX, topY);
    // Shape::GetInstance().DrawPixel(rightX, topY);
    // Shape::GetInstance().DrawPixel(rightX, bottomY);
    // Shape::GetInstance().DrawPixel(LeftX, bottomY);

    Shape::GetInstance().DrawPixel(centerX, centerY);

    float c = radius * radius;

    for(float x = LeftX+1; x < rightX; x++)
    {
        
        for(float y = topY+1; y < bottomY; y++)
        {
            float a = centerX - x;
            float b = centerY - y;

            if( ((a*a) + (b*b) == c) || (((a*a) + (b*b) <= c) && ((a*a) + (b*b) >= c)) )
            {
                //printf("Drawing at: %f, %f\n",x,y);
                Shape::GetInstance().DrawPixel(float(x), float(y));
            }
        }

    }

}