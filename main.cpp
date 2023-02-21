/*
LÃ m theo tutorial táº¡i:
http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-2-dont-put-everything-in-main
*/
#include <iostream>
#include <SDL.h>
//#include <SDL2/SDL.h>

using namespace std;

//**************************************************************
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Load Bitmap Image in SDL";

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
//**************************************************************

// Hai hÃ m vá» texture, láº¥y nguyÃªn vá» tá»«tutorial táº¡i:
// http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-2-dont-put-everything-in-main

// HÃ m náº¡p texture tá»« file áº£nh, Ä‘á»ƒ váº½ lÃªn renderer tÆ°Æ¡ng á»©ng
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

// HÃ m Ä‘Æ°a texture ra renderer (Ä‘á»ƒ hiá»ƒn thá»‹ ra mÃ n hÃ¬nh) táº¡i toáº¡ Ä‘á»™ (x,y) vÃ  giá»¯ nguyÃªn kÃ­ch cá»¡ ban Ä‘áº§u cá»§a áº£nh
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

// HÃ m (cÃ¹ng trÃªn nhÆ°ng khÃ¡c tham sá»‘ vá»›i hÃ m ngay trÃªn)
// Ä‘Æ°a texture ra renderer (Ä‘á»ƒ hiá»ƒn thá»‹ ra mÃ n hÃ¬nh) táº¡i toáº¡ Ä‘á»™ (x,y) vÃ 
// vá»›i kÃ­ch cá»¡ rá»™ng (w) vÃ  cao (h) cho trÆ°á»›c.
// áº¢nh sáº½ Ä‘Æ°á»£c co dÃ£n (phÃ³ng to thu nhá») cho khá»›p kÃ­ch cá»¡ nÃ y.
// ÄÃ¢y lÃ  hÃ m khÃ´ng cÃ³ trong tutorial ban Ä‘áº§u, Ä‘Æ°á»£c sá»­a tá»« hÃ m trong tutorial.
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    //Náº¡p áº£nh ná»n vÃ o má»™t biáº¿n texture
    SDL_Texture *background = loadTexture("background.bmp", renderer);
    //Náº¡p áº£nh vÃ o má»™t biáº¿n texture
    SDL_Texture *image = loadTexture("image.bmp", renderer);
    //Náº¿u cÃ³ lá»—i thÃ¬ giáº£i phÃ³ng hai texture Ä‘Ã£ náº¡p, rá»“i káº¿t thÃºc
    if (background == nullptr || image == nullptr){
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(image);
        quitSDL(window, renderer);
    }

    //XoÃ¡ mÃ n hÃ¬nh
    SDL_RenderClear(renderer);

    //Váº½ áº£nh ná»n vÃ o toÃ n bá»™ cá»­a sá»•
    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Váº½ áº£nh táº¡i vá»‹ trÃ­ vÃ  kÃ­ch cá»¡ má»›i (áº£nh bá»‹ co láº¡i cho khá»›p)
    renderTexture(image, renderer, 50, 50, 30, 30);

    //Váº½ áº£nh vÃ o giá»¯a mÃ n hÃ¬nh, giá»¯ nguyÃªn kÃ­ch cá»¡ ban Ä‘áº§u cá»§a áº£nh
    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;
    renderTexture(image, renderer, x, y);

    // DÃ¹ng lá»‡nh hiá»ƒn thá»‹ (Ä‘Æ°a) hÃ¬nh Ä‘Ã£ váº½ ra mÃ nh hÃ¬nh
   //Khi thÃ´ng thÆ°á»ng cháº¡y vá»›i mÃ´i trÆ°á»ng bÃ¬nh thÆ°á»ng á»Ÿ nhÃ 
    SDL_RenderPresent(renderer);
   //Khi cháº¡y á»Ÿ mÃ¡y thá»±c hÃ nh WinXP á»Ÿ trÆ°á»ng (mÃ¡y áº£o)
   //SDL_UpdateWindowSurface(window);

   //Äá»£i 1 phÃ­m báº¥t ká»³ trÆ°á»›c khi Ä‘Ã³ng cá»­a sá»•
    waitUntilKeyPressed();

    //Giáº£i phÃ³ng 2 biáº¿n texture Ä‘Ã£ dÃ¹ng
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image);
    //Káº¿t thÃºc SDL (giáº£i phÃ³ng cÃ¡c biá»ƒn window vÃ  renderer)
    quitSDL(window, renderer);
    return 0;
}

/**
* Náº¡p má»™t áº£nh bitmap (BMP) vÃ o má»™t texture trÃªn thiáº¿t bá»‹ hiá»‡n thá»‹ (rendering device)
* @param file: Ä‘Æ°á»ng dáº«n vÃ  tÃªn file áº£nh BMP
* @param ren: renderer Ä‘á»ƒ náº¡p texture lÃªn
* @return tráº£ vá» texture Ä‘Ã£ náº¡p, hoáº·c nullptr náº¿u cÃ³ lá»—i.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	//Khá»Ÿi táº¡o lÃ  nullptr Ä‘á»ƒ trÃ¡nh lá»—i 'dangling pointer'
	SDL_Texture *texture = nullptr;
	//Náº¡p áº£nh tá»« tÃªn file (vá»›i Ä‘Æ°á»ng dáº«n)
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//Náº¿u khÃ´ng cÃ³ lá»—i, chuyá»ƒn Ä‘á»•i vá» dáº¡ng texture and vÃ  tráº£ vá»
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Äáº£m báº£o viá»‡c chuyá»ƒn Ä‘á»•i khÃ´ng cÃ³ lá»—i
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

/**
* Váº½ má»™t SDL_Texture lÃªn má»™t SDL_Renderer táº¡i toáº¡ Ä‘á»™ (x, y), trong khi
* giá»¯ nguyÃªn chiá»u rá»™ng vÃ  cao cá»§a áº£nh
* @param tex: texture nguá»“n chÃºng ta muá»‘n váº½ ra
* @param ren: thiáº¿t bá»‹ renderer chÃºng ta muá»‘n váº½ vÃ o
* @param x: hoÃ nh Ä‘á»™
* @param y: tung Ä‘á»™
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Thiáº¿t láº­p hÃ¬nh chá»¯ nháº­t Ä‘Ã­ch mÃ  chÃºng ta muá»‘n váº½ áº£nh vÃ o trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy váº«n texture Ä‘á»ƒ láº¥y chiá»u rá»™ng vÃ  cao (vÃ o chiá»u rá»™ng vÃ  cao tÆ°Æ¡ng á»©ng cá»§a hÃ¬nh chá»¯ nháº­t Ä‘Ã­ch)
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //ÄÆ°a toÃ n bá»™ áº£nh trong texture vÃ o hÃ¬nh chá»¯ nháº­t Ä‘Ã­ch
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
* Váº½ má»™t SDL_Texture lÃªn má»™t SDL_Renderer táº¡i toáº¡ Ä‘á»™ (x, y), vá»›i
* chiá»u rá»™ng vÃ  cao má»›i
* @param tex: texture nguá»“n chÃºng ta muá»‘n váº½ ra
* @param ren: thiáº¿t bá»‹ renderer chÃºng ta muá»‘n váº½ vÃ o
* @param x: hoÃ nh Ä‘á»™
* @param y: tung Ä‘á»™
* @param w: chiá»u rá»™ng (má»›i)
* @param h: Ä‘á»™ cao (má»›i)
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Thiáº¿t láº­p hÃ¬nh chá»¯ nháº­t Ä‘Ã­ch mÃ  chÃºng ta muá»‘n váº½ áº£nh vÃ o trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
    //ÄÆ°a toÃ n bá»™ áº£nh trong texture vÃ o hÃ¬nh chá»¯ nháº­t Ä‘Ã­ch
    //(áº£nh sáº½ co dÃ£n cho khá»›p vá»›i kÃ­ch cá»¡ má»›i)
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

//*****************************************************
// CÃ¡c hÃ m chung vá» khá»Ÿi táº¡o vÃ  huá»· SDL
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi thÃ´ng thÆ°á»ng cháº¡y vá»›i mÃ´i trÆ°á»ng bÃ¬nh thÆ°á»ng á»Ÿ nhÃ 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi cháº¡y á»Ÿ mÃ¡y thá»±c hÃ nh WinXP á»Ÿ trÆ°á»ng (mÃ¡y áº£o)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
//**************************************************************

