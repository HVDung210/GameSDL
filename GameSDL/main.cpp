#include <SDL.h>
#include <SDL_image.h>

#include "SDL_untils.h"
#include "BaseObject.h"
#include "map.h"


BaseObject g_background;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
    {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");;

    gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL)
    {
        success = false;
    }
    else
    {
        gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if(gScreen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if( !(IMG_Init(imgFlags) && imgFlags))
                success = false;


        }

    }

    return success;
}

bool LoadBackground()
{

    bool ret = g_background.LoadImg("image//background.png", gScreen);
    if(ret == false)
        return false;

    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();

}

int main(int argc, char* argv[])
{
    if(InitData() == false)
        return -1;

    if(LoadBackground() == false)
        return -1;

    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(gScreen);


    bool is_quit = false;
    while(!is_quit)
    {
        while(SDL_PollEvent(&gEvent) != 0)
        {
            if(gEvent.type == SDL_QUIT)
            {
                is_quit = true;
            }
        }

        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        g_background.Render(gScreen, NULL);
        game_map.DrawMap(gScreen);


        SDL_RenderPresent(gScreen);

    }


    close();

    return 0;
}


