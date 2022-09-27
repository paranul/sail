#pragma once


#ifdef _WIN32
#include <SDL.h>
#elif __linux__
#include <SDL2/SDL.h>
#endif

//INFO: Static Shape Class
//INFO: Wrapper around some common SDL shapes and a few extensions, call with Shape::GetInstace().
class Shape
{

public:
    static Shape& GetInstance();

    void DrawRect(int x, int y, int width, int height);
    void DrawPixel(int x, int y);
    //TODO:: Maybe change radius to float? to consider
    void DrawCircle(int centerX, int centerY, int radius);
    void DrawCircleF(float centerX, float centerY, float radius);
    void DrawLine(int x1, int y1, int x2, int y2);


private:


    Shape(){}
    ~Shape(){}


};