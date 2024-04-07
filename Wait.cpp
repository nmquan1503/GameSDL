#include "Wait.h"

Wait::Wait(const LoaderParams* Params,int speed):SDLGameObject(Params),p_speed(speed)
{

}

void Wait::update()
{
    time+=1000/16*p_speed;
    p_Frame=(++p_Frame)%3;
    p_Row=std::min(3,time/1000);
}

void Wait::draw()
{
    SDLGameObject::draw();
}

void Wait::clean()
{
    SDLGameObject::clean();
}
