#ifndef _Animation_h_
#define _Animation_h_

#include "SDL_GameObject.h"
#include "LoaderParams.h"

class Animation : public SDLGameObject
{
private:
    int time=0;
    int p_Frame_max;
public:
    Animation(const LoaderParams* Params,int Frame_max);
    int GetTime(){return time;}
    void update();
    void draw();
    void clean();

};

#endif // _Animation_h_
