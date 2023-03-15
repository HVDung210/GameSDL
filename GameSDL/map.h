#ifndef MAP_H;
#define MAP_H;

#include "SDL_untils.h"
#include "BaseObject.h"


#define MAX_TILES 20

class TileMat : public BaseObject
{
public:
    TileMat(){;}
    ~TileMat(){;}

};

class GameMap
{
public:
    GameMap(){;}
    ~GameMap(){;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);



private:
    Map game_map;
    TileMat tile_mat[MAX_TILES];

};



#endif // MAP_H
