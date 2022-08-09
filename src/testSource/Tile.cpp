
#ifdef _WIN32
#include <SDL.h>
#include "Tile.h"
#elif __linux__
#include <SDL2/SDL.h>
#include "Tile.h"
#endif

TestTile::TestTile()
:
    m_x(0),
    m_y(0)
{

}

TestTile::TestTile(int x, int y)
:  
    m_x(x),
    m_y(y)
{

}

void TestTile::DrawUknownTileXY(int x, int y)
{
    m_x = x;
    m_y = y;
    //Filled Rect
    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255,255, 255);
    SDL_Rect rect = {m_x, m_y, m_size, m_size};
    SDL_RenderFillRect(Game::GetInstance().GetRenderer(), &rect);

    //Outline
    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0,0, 255);
    SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &rect);

    //Strike through line
    SDL_RenderDrawLine(Game::GetInstance().GetRenderer(), m_x, m_y, m_x + m_size -1 ,  m_y +m_size -1);
}

void TestTile::DrawUknownTile()
{
    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255,255, 255);
    SDL_Rect rect = {m_x, m_y, m_size, m_size};
    SDL_RenderFillRect(Game::GetInstance().GetRenderer(), &rect);

    //Outline
    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0,0, 255);
    SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &rect);

    //Strike through line
    SDL_RenderDrawLine(Game::GetInstance().GetRenderer(), m_x, m_y, m_x + m_size -1 ,  m_y + m_size -1);
}


int TestTile::GetSize()
{
    return m_size;
}