
#include "S_Draw.h"
#include "../Game.h"
#include <iostream>
#include <filesystem>

bool POINTER::S_Draw::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr)
    {
        printf("Failed to load Surface-> %s, %s\n", filename.c_str(), SDL_GetError() );
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    if(texture == nullptr)
    {
        printf("Failed to load Texture-> %s, %s", filename.c_str(), SDL_GetError() );
        return false;
    }

    m_textures[id] = texture;

    return true;

}

bool POINTER::S_Draw::LoadID(std::string filename)
{
    //IMG_LoadTexture
    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), filename.c_str());
    if(texture == nullptr)
    {
        printf("Failed to load Texture-> %s, %s", filename.c_str(), SDL_GetError() );
        return false;
    }

    std::string id = POINTER::S_Draw::StripFilenameExtension(filename);


    m_textures[id] = texture;

    return true;
}


void POINTER::S_Draw::DrawQueriedTexture(std::string id, int x, int y, SDL_RendererFlip flip)
{

    //TODO: Search texture ID is already loaded into the std::map -> search map to see if the incoming string::id does not match anything in the 
    //std::map<std::string, SDL_Texture*> m_textures, and then draw the unknown SDL_Draw function tile (code is already in the Tile.cpp)


    //__debugbreak();
    int width = 0;
    int height = 0;

    SDL_QueryTexture(m_textures[id], NULL, NULL, &width, &height);
    SDL_Rect srcRect = {0,0,width, height};
    SDL_Rect dstRect = {(int)((x * m_scale) + m_offsetX ),  (int)((y * m_scale) + m_offsetY ), (int)(width * m_scale), (int)(height * m_scale)};

    //std::cout << "RectX: " <<dstRect.x << " RectY: "<<dstRect.y << std::endl;

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), m_textures[id], &srcRect, &dstRect, 0, nullptr, flip);
}

std::string POINTER::S_Draw::StripFilenameExtension(std::string filename)
{
    std::filesystem::path path(filename);
    // std::cout << std::filesystem::path(filename) << std::endl;
    // std::cout << std::filesystem::path(filename).stem();

    filename = path.stem().u8string();

    return filename;
}