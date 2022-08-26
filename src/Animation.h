
#ifdef _WIN32
#include <SDL.h>

#elif __linux__
#include<SDL2/SDL.h>
#endif

#include <string>



class Animation
{

public:
    Animation();
    void SetProperties(std::string textureID, int spriteRow, int frameCount, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Update();
    void Draw(int x, int y, int spriteWidth, int spriteHeight);

private:
    std::string m_textureID;
    int m_spriteRow;
    int m_frameCount;
    int m_animationSpeed;
    SDL_RendererFlip m_flip;
    int m_spriteFrame;


};