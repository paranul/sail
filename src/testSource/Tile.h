#pragma once




////NOTES////
/*

    dont include Game.h in header files... causes circular dependency

    This is seperate from the S_Draw class (Static Texture manager and whatever else comes after that, which will be affected by the camera)
    this will just draw differnt colored tiles in their appropriate screen space
*/

class TestTile
{

public:

    TestTile();
    //~TestTile();
    TestTile(int x, int y);


    void DrawUknownTileXY(int x, int y);
    void DrawUknownTile();
    //void DrawFloorTile(int x, int y);
    //void DrawWallTile(int x, int y);
    //void DrawRoofTile(int x, int y);
    //static int GetSize();





private:

    int m_x;
    int m_y;

    // float m_scale = 1.0f;
    // int m_offsetX = 0;
    // int m_offsetY = 0;

    unsigned int m_size = 32 ;

};





/* How to use

    //One Object
    Tile rect1;
    rect1.Draw(0,0);


    // C-Array / vectors
    Tile tiles[5];
    std::vector<Tile> tiles{5};

    for( int i = 0; i < 5; i++)
    {
        tiles[i].Draw(i * 100, 200);
    }


    // std::vector
    std::vector<Tile> tiles;

    for(int i = 0; i < 100; i++)
    {
         tiles.push_back( Tile(i * rand() % 1000,i * rand() % 1000) );
    }

    for(auto& tile : tiles)
    {
        tile.DrawTile();
    }


*/


//Pointer FAQ:



/*

Question:
what does the const mean around pointers, before the int and between the star and the name

int Sum(int* p, int size)
{
    int sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum+=p[i];

    }
    return sum;
}


means that this pointer cannot 
be used to modify what its pointing to
           ^^
int Sum(//const// int* //cosnt// p, int size)
                            \/
            means you cant retarget
            the pointer

{
    int sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum+=p[i];

    }
    return sum;
}

*/