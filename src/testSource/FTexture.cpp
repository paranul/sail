
#include "FTexture.h"
#include "../Game.h"


void FTexture::LoadMedia(std::string filePath)
{
    bool sucess = true;

    m_font = TTF_OpenFont(filePath.c_str(), 28);
    if(m_font == nullptr)
    {
        printf("m_font failed to open %s \n", filePath.c_str());
        sucess = false;
    }

    else
    {
        SDL_Color textColor = {0, 0 , 0 };
    }
}

void FTexture::LoadFont(std::string path, int size)
{
    m_font = TTF_OpenFont(path.c_str(), size);

    if(m_font == nullptr)
    {
        printf("m_font failed to open %s \n", path.c_str());
    }

}

//This is for images, not text
bool FTexture::LoadFromFile(std::string path)
{
    //the final texture
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr)
    {
        printf("error at loadedSurface: %s SDL_Image Error: %s",path.c_str(), IMG_GetError());
        //return m_texture = nullptr; //I Think I should return this? might need to comment it out and check or maybe return false?
    }
    else
    {
        m_width = loadedSurface->w;
        m_height = loadedSurface->h;
    }

    SDL_FreeSurface(loadedSurface);

    m_texture = newTexture;
    return m_texture != nullptr; 

}

bool FTexture::LoadFromRenderedText(std::string displayText, SDL_Color textColor )
{
    //free(); Needed?

    //TODO: Need to load m_font (Pass into the function or seperate load?)
    //TODO: since this is a bool type function, add negative success values to NULL texture / surface

    //RenderText Surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, displayText.c_str(), textColor);
    if(textSurface == nullptr)
    {
        printf("{FTexture.cpp, line: %d} Error: textSurface == nullptr | SDL_TTF ERROR: %s\n",__LINE__, TTF_GetError());
        //TTF_GetError()
    }
    else
    {
        //convert surface to texture
        m_texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), textSurface);
        if(m_texture == nullptr)
        {
            printf("Error creating TEXTURE from SURFACE, SDL_ERROR: %s", SDL_GetError());
            //TODO: since this is a bool type function, add negative success values to NULL texture / surface?
        }
        else
        {
            //have to use surface to get the dimension of the image
            m_width = textSurface->w;
            m_height = textSurface->h;
        }

        //Free the old surface, now in m_texture
        SDL_FreeSurface(textSurface);
    }


    return m_texture != nullptr;

}

void FTexture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, m_width, m_height};

    if(clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), m_texture, clip, &renderQuad, angle, center, flip);
}