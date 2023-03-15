#ifndef SDL_UNTILS__H
#define SDL_UNTILS__H


#include <windows.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent ;


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0Xff;

#define TILE_SIZE 64
#define MAP_MAP_X 400
#define MAP_MAP_Y 10


typedef struct Map
{
    int start_x;
    int start_y;

    int max_x;
    int max_y;

    int tile[MAP_MAP_Y][MAP_MAP_X];
    char* file_name;

};

#endif // SDL_UNTILS__H
