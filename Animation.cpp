#include "Animation.h"

Animation::Animation(const LoaderParams* Params,int Frame_max):SDLGameObject(Params),p_Frame_max(Frame_max){}

void Animation::update()
{
    time++;
    p_Frame=(++p_Frame)%p_Frame_max;

}

void Animation::draw()
{
    SDLGameObject::draw();
}

void Animation::clean()
{
    SDLGameObject::clean();
}
