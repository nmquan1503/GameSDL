#include "SDL_GameObject.h"
#include "ManageTexture.h"
#include "Game.h"
#include "GameObject.h"

SDLGameObject::SDLGameObject(const LoaderParams* p_Params):GameObject(p_Params),p_pos(p_Params->GetX(),p_Params->GetY()),p_vel(0,0),p_acc(0,0)
{
    p_w=p_Params->GetW();
    p_h=p_Params->GetH();
    p_TexID=p_Params->GetTexID();
    p_Frame=0;
}

void SDLGameObject::draw()
{
    ManageTexture::GetInstance()->drawFrame(p_TexID,(int)p_pos.GetX(),(int)p_pos.GetY(),p_w,p_h,p_Frame,Game::GetInstance()->GetRenderer(),flip);
}

void SDLGameObject::update()
{
    p_vel+=p_acc;
    p_pos+=p_vel;
}

void SDLGameObject::drawBG()
{
    ManageTexture::GetInstance()->draw(p_TexID,(int)p_pos.GetX(),(int)p_pos.GetY(),p_w,p_h,Game::GetInstance()->GetRenderer(),flip);
}

void SDLGameObject::clean()
{
    ManageTexture::GetInstance()->clearFromTexMap(p_TexID);
}
