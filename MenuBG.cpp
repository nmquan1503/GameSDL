#include "MenuBG.h"

MenuBG:: MenuBG(const LoaderParams* Params,int Fpls):SDLGameObject(Params),p_Fpls(Fpls) {}

void MenuBG::draw()
{
    SDLGameObject::drawBG();
}

void MenuBG::update()
{
    p_vel.SetX(p_Fpls);
    SDLGameObject::update();
    if((int)p_pos.GetX()==-1020)
        p_pos.SetX(p_Fpls);
}

void MenuBG::clean()
{
    SDLGameObject::clean();
}
