
#include "dart.h"

Dart::Dart(const LoaderParams* Params,Vector2D fir,Vector2D sec):SDLGameObject(Params),fir_pos(fir),sec_pos(sec){}

void Dart::draw()
{
    SDLGameObject::draw();
}

void Dart::update()
{
    p_Frame=(++p_Frame)%2;
    Vector2D vec=(sec_pos-fir_pos);
    vec.normal();
    vec*=40;
    p_vel=vec;
    SDLGameObject::update();
    time++;
}

void Dart::clean()
{
    ;
}
