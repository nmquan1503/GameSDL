#include "MenuBG.h"

MenuBG:: MenuBG(const LoaderParams* Params,int Fpls,int max_x):SDLGameObject(Params),p_Fpls(Fpls)
{
    p_max_x=max_x;
}

void MenuBG::draw()
{
    ManageTexture::GetInstance()->drawXPls(p_TexID,p_pos.GetX(),p_pos.GetY(),p_w,p_h,pos_x,Game::GetInstance()->GetRenderer());
}

void MenuBG::update()
{
    /*p_vel.SetX(p_Fpls);
    SDLGameObject::update();
    if((int)p_pos.GetX()==-1020)
        p_pos.SetX(p_Fpls);*/
    pos_x+=p_Fpls;
    if(pos_x==(p_max_x-p_w))pos_x=0;
}

void MenuBG::clean()
{
    SDLGameObject::clean();
}
