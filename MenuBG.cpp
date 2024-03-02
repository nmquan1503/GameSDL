#include "MenuBG.h"

MenuBG:: MenuBG(const LoaderParams* Params):SDLGameObject(Params) {}

void MenuBG::draw()
{
    SDLGameObject::drawBG();
}

void MenuBG::update()
{
    p_vel.SetX(-5);
    SDLGameObject::update();
    if((int)p_pos.GetX()==-1020)
        p_pos.SetX(-5);
}

void MenuBG::clean()
{
    ;
}
