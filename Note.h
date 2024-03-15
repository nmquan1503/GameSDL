#ifndef _Note_h_
#define _Note_h_

#include "SDL_GameObject.h"
#include "ManageFont.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Note
{
private:
    int time=0;
    SDL_Texture* p_tex;
    int p_x;
    int p_y;
    int p_w;
    int p_h;
    SDL_Color p_color;
public:
    Note(std::string id,std::string text,int x_mid,int y,int w_max,SDL_Color color);
    int GetTime(){return time;}
    void update();
    void draw();
    void clean();
};

#endif // _Note_h_
