
#ifdef _WIN32
#include <SDL.h>
#elif __linux__
#include <SDL2/SDL.h>
#endif



class Shape
{

public:
    static Shape& GetInstance();

    void DrawRect(int x, int y, int width, int height);
    void DrawPixel(int x, int y);
    //TODO:: Maybe change radius to float? to consider
    void DrawCircle(int centerX, int centerY, int radius);
    void DrawLine(int x1, int y1, int x2, int y2);


private:

    Shape(){}
    ~Shape(){}


};