
#include <chrono>

class Timer
{

private:
    //the time point at the start of the timer and end of the timer
    long long m_start = 0;
    long long m_end = 0;


    std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint;

public:
    Timer()
    {
        Start();
    }

    void Start()
    {
        m_startPoint = std::chrono::high_resolution_clock::now();
    }

    long long Elapsed()
    {
        using namespace std::chrono;
        auto endPoint = high_resolution_clock::now();

        m_start = time_point_cast<microseconds>(m_startPoint).time_since_epoch().count();
        m_end = time_point_cast<microseconds>(endPoint).time_since_epoch().count();

        return m_end - m_start;
    }


    

};