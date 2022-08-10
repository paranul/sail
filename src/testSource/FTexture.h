#ifndef F_TEXTURE_H
#define F_TEXTURE_H

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#elif __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#endif

#include <string>

//Lazy Foo texture class 
class FTexture
{

public:
    void LoadMedia(std::string filePath);
    //I think this is just for loading images
    bool LoadFromFile(std::string path);
    //This is for the text you want to display
    bool LoadFromRenderedText(std::string displayText, SDL_Color textColor = {255,255,255});
    void Render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void LoadFont(std::string file, int size);

    void SetBlendMode();


private:

SDL_Texture* m_texture;
TTF_Font* m_font;
int m_width;
int m_height;

};


#endif