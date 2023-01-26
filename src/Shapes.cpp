
#include "Shapes.h"
#include "Game.h"
#include "../external/glm/glm.hpp"
#include <cmath>

#include <vector>



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

void Shape::DrawRect(float x, float y, float width, float height)
{
    SDL_FRect rect = {x, y, width, height};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255,0,0,255);
    SDL_RenderDrawRectF(Game::GetInstance().GetRenderer(), &rect);
}

void Shape::DrawLine(int x1, int y1, int x2, int y2)
{
    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255,0,0,255);
    SDL_RenderDrawLine(Game::GetInstance().GetRenderer(), x1, y1, x2, y2);
}

void Shape::DrawLine(float x1, float y1, float x2, float y2)
{
    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255,0,0,255);
    SDL_RenderDrawLineF(Game::GetInstance().GetRenderer(), x1, y1, x2, y2);
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

    // Shape::GetInstance().DrawPixel(LeftX, topY);
    // Shape::GetInstance().DrawPixel(rightX, topY);
    // Shape::GetInstance().DrawPixel(rightX, bottomY);
    // Shape::GetInstance().DrawPixel(LeftX, bottomY);

    // Shape::GetInstance().DrawPixel(centerX, centerY);

    for(int x = LeftX; x <= rightX; x++)
    {
        
        for(int y = topY; y <= bottomY; y++)
        {
            int a = centerX - x;
            int b = centerY - y;

            if( sqrt((a*a) + (b*b)) <= radius)
            {
                Shape::GetInstance().DrawPixel(x, y);
            }
        }

    }

}

void Shape::DrawMark(Point<int> center, int radius, SDL_Color c)
{
    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), c.r, c.g, c.b, 255);

    for(int i = 0; i <= (radius * 2); i ++)
    {
        SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(),center.x - (i - radius), center.y);
    }

    for(int i = 0; i <= (radius * 2); i ++)
    {
        SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(),center.x, center.y - (i-radius));
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

    Shape::GetInstance().DrawPixel(int(centerX), int(centerY));

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
                Shape::GetInstance().DrawPixel(int(x), int(y));
            }
        }

    }

}

void Shape::DrawPGECircle(int centerX, int centerY, int radius)
{
    std::vector<std::pair<int, int>> modelCircle;

    modelCircle.push_back({centerX,centerY});

    int nPoints = 20;
}