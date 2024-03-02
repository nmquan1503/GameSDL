
#include<SDL2/SDL.h>

#include<time.h>

#include "Game.h"


const int FPS=14;
const int DELAY_TIME = 1000.0f/FPS;



int main(int argc,char* argv[])
{

    srand(time(0));

    Uint32 frameStart,frameTime;

    Game::GetInstance()->init("Giải cứu Sugar Tank",1020,600);
    while(Game::GetInstance()->IsRunning())
    {
        frameStart=SDL_GetTicks();

        Game::GetInstance()->handleEvents();
        Game::GetInstance()->update();
        Game::GetInstance()->render();

        frameTime=SDL_GetTicks()-frameStart;
        if(frameTime< DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }
    Game::GetInstance()->clean();
    return 0;
}
