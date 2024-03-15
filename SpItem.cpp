
#include "SpItem.h"

SpItem::SpItem(const LoaderParams* Params,std::string ID):SDLGameObject(Params),SpID(ID)
{
    time=0;
}

void SpItem::update()
{
    time+=62.5;
}

void SpItem::draw()
{
    SDLGameObject::draw();
    int t=9-(int)(time/1000);
    std::string tmp=std::to_string(t)+"s";
    ManageFont::GetInstance()->drawTextBlended("font3",tmp,{255,255,0,255},p_pos.GetX()+20,p_pos.GetY()+60,Game::GetInstance()->GetRenderer());
}
void SpItem::clean()
{

}
