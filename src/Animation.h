#ifndef ANIMATION_H
#define ANIMATION_H


#ifdef _WIN32
#include <SDL.h>

#elif __linux__
#include<SDL2/SDL.h>
#endif

#include <string>






class Animation
{

public:

/*
    This Animation::State format needs to be strictly followed when creating sprite sheets ...
    i.e the first (row # 0) will be the IDLE animation, the second (row # 1) will be WALK animation pointing right
    the 3rd (row # 2) will be RUN animation poiting to the right e.t.c
*/
// static enum State
// {
//     IDLE,
//     WALK,
//     RUN
// };

public:
    Animation() {}
//          std::string textureID needs to already have been loaded from TextureManager()
//          m_animationSpeed # will dictate how many milliseconds per frame
//          spriteRow will correspont to Animation::State
//          spriteWidth & spriteHeight should ideally be 32 x 32 but will likely vary for large objects / creatures
    void SetProperties(std::string textureID, int spriteRow, int frameCount, int spriteWidth, int spriteHeight, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Update();
    void Draw(int x, int y, int spriteWidth, int spriteHeight);
    void Draw(int x, int y);
    void Draw(float x, float y);
    const int GetFrame();

private:
    std::string m_textureID;
    int m_spriteRow;
    int m_frameCount;
    int m_animationSpeed;
    int m_spriteWidth;
    int m_spriteHeight;
    SDL_RendererFlip m_flip;
    int m_spriteFrame;

    
    


};

#endif



/*

    All animation States start at default looking to the right -> (+X)
    In order to flip them <- (-X) Call SDL_FLIP_HORIZONTAL and then SDL_FLIP_NONE to revert back to -> (+X)








*/