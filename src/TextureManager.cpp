

#include <filesystem>
#include "TextureManager.h"
#include "Game.h"
#include "Shapes.h"
#include <iostream>

TextureManager& TextureManager::GetInstance()
{
    static TextureManager instance;
    return instance;
}

TextureManager::TextureManager()
{
    std::cout << "TextureManager::map_size: " << m_textureMap.size() << '\n';
}

//TODO: Might consider making this a boolean to see if the load was all good or not
void TextureManager::Load(std::string fileName)
{

    //IMG_LoadTexture doesnt need to make surface first
    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(),fileName.c_str());
    if(texture == nullptr)
    {
        printf("Failed to load Texture-> %s, %s", fileName.c_str(), SDL_GetError() );
        //return false;
    }

    std::string id = StripFileNameExtension(fileName);
    m_textureMap[id] = texture;

}


void TextureManager::DrawObject(std::string id, int x, int y, SDL_RendererFlip flip)
{
    int width = 0;
    int height = 0;

    SDL_QueryTexture(m_textureMap[id], NULL, NULL, &width, &height);

    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width , height };

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), m_textureMap[id], &srcRect, &dstRect, 0, NULL, flip);
}

//TODO::Create a class that will act as a wrapper for the double angle but resets it to 0 when it goes past 360.
void TextureManager::DrawRotatingObject(std::string id, int x, int y, double angle, const SDL_Point *center,  SDL_RendererFlip flip)
{
    int width = 0;
    int height = 0;

    SDL_QueryTexture(m_textureMap[id], NULL, NULL, &width, &height);

    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width, height};

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), m_textureMap[id], &srcRect, &dstRect, angle, center, flip);

    ////DEBUG Draw Center of object rotation////////////////////////////////////////////////
    int centerX = 0;                                                                        //
    int centerY = 0;                                                                        //
                                                                                            //
    if(center == nullptr)                                                                   //
    {                                                                                       //
        centerX = width / 2;        
        centerY = height / 2;
    }
    else
    {
        centerX = center->x;
        centerY = center->y;
    }
    Shape::GetInstance().DrawCircle(dstRect.x + centerX, dstRect.y + centerY, 2);

    /////////////////////////////////////////////////////////////////////////////////////
}

void TextureManager::DrawObjectDimensions(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width, height};

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), m_textureMap[id], &srcRect, &dstRect, 0, NULL, flip);


    //DEBUG//////////////////////////////////////////////////////////

    //Shape::GetInstance().DrawRect(x, y, width, height);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width * frame, height * row, width, height};
    SDL_Rect dstRect = {x, y, width , height };
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), m_textureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}


std::string TextureManager::StripFileNameExtension(std::string fileName)
{
    std::filesystem::path path(fileName);

    fileName = path.stem().u8string();

    return fileName;
}