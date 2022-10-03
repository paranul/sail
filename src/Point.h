#pragma once

//Just a simple templated collection for X and Y coordinates....
template<typename T>
class Point
{

public:
    Point()
    {
        T x = 0;
        T y = 0;
    }
    Point(T x_in, T y_in)
    {
        this->x = x_in;
        this->y = y_in;
    }

    Point operator =(Point &rhs)
    {
        Point lhs;
        lhs.x = rhs.x;
        lhs.y = rhs.y;

        return lhs;
    }

    void Print()
    {
        std::cout << "(" << Point<T>::x <<"," << Point<T>::y << ")\n";
    }



public:
    T x;
    T y;

};