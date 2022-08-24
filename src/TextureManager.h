
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#elif __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include <string>
#include <map>


class TextureManager
{

public:
    static TextureManager& GetInstance();

    //The filename without extension gets converted to the ID
    //i.e "../assets/adventurer.png" filename =  textureID = "adventuerer"
    void Load(std::string fileName);
    //DrawObject is subject to zoom level and camera position, int x & y = screen space
    void DrawObject(std::string id, int x, int y, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawRotatingObject(std::string id, int x, int y, double angle, const SDL_Point *center,  SDL_RendererFlip flip = SDL_FLIP_NONE);


    //TODO:: NOT WORKING YET
    void DrawObjectDimensions(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);

    std::string StripFileNameExtension(std::string fileName);


private:

TextureManager() {}
~TextureManager() {}

//const char* id, SDL_Texture* texture
std::map<std::string, SDL_Texture*> m_textureMap;

};