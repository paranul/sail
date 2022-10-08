#ifndef S_DRAW_H
#define S_DRAW_H


#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#elif __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <map>
#include <string>

//INFO: Static / Singleton Texture Manager / Drawer
//      Uses pointer which i believe leads valgrind to think that this is a leak
namespace POINTER
{
    class S_Draw
    {

    public:
        static S_Draw* GetInstance()
        {
            return s_instance = (s_instance != nullptr) ? s_instance : new S_Draw();
        }
        //INFO: The filename becomes the texture ID
        bool LoadID(std::string filename);
        //INFO: Load a file and give it a texture ID / Name
        bool Load(std::string id, std::string filename);

        //INFO: Strip the filepath and extensions out of filenames, e.g: "C:/assets/hero.png" = "hero" using path.stem()
        std::string StripFilenameExtension(std::string filename);

        //INFO: Draw a texture, must provide width and height of the texture.
        void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
        //INFO: Draw a texture, width and height is automatically calculated by SDL_QueryTexture()
        void DrawQueriedTexture(std::string id, int x, int y, SDL_RendererFlip flip = SDL_FLIP_NONE);
        SDL_Texture* GetTexture(std::string id);


       //bool FooLoadFromRendererdText(std::string textureText, SDL_Color textColor);




        //TODO: Make some getters for this maybe?
        float m_scale = 1.0f;
        int m_offsetX = 0;
        int m_offsetY = 0;


    private:
        S_Draw() = default;
        ~S_Draw() = default;

        //TODO: Experiment with other containers, perhaps unsorted map? perhaps vectors with the id being the iterator? Perhaps unsorted map with int id?
        std::map<std::string, SDL_Texture*> m_textures;
        static inline S_Draw* s_instance = nullptr;

    };

}



#endif