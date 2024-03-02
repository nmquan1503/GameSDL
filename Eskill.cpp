
#include "Eskill.h"

Eskill::Eskill(const LoaderParams* Params,Vector2D fir,Vector2D sec,bool fl):SDLGameObject(Params),fir_pos(fir),sec_pos(sec){flip=fl;}

void Eskill::draw()
{
    SDLGameObject::draw();
}

void Eskill::update()
{
    Vector2D vec=sec_pos-fir_pos;
    vec.normal();
    vec*=100;
    if(time>=4)
    {
        p_vel=vec;
    }
    p_Frame++;
    time++;
    SDLGameObject::update();
}

void Eskill::clean()
{
    ;
}
