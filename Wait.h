#ifndef _Wait_h_
#define _Wait_h_

#include "SDL_GameObject.h"

class Wait : public SDLGameObject
{
private:
    int time=0;
    int p_speed;
public:
    Wait(const LoaderParams* Params,int speed);

    virtual void update();
    virtual void draw();
    virtual void clean();

    int GetTime(){return time;}
};


#endif // _Wait_h_
