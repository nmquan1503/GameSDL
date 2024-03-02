
#include "MenuButton.h"

MenuButton::MenuButton(const LoaderParams* p_Params,void(*callback)()):SDLGameObject(p_Params),p_callback(callback)
{
    p_Frame=MOUSE_OUT;
}

/*void MenuButton::load(const LoaderParams* Params)
{
    SDLGameObject::load(Params);
    p_callbackID=Params->GetCallBackID();
}*/

void MenuButton::draw()
{
    SDLGameObject::draw();
}

void MenuButton::update()
{
    Vector2D* MousePos=HandleInput::GetInstance()->GetMousePos();
    if(MousePos->GetX()<(p_pos.GetX()+p_w) && MousePos->GetX()>p_pos.GetX() && MousePos->GetY()<(p_pos.GetY()+p_h) && MousePos->GetY()>p_pos.GetY())
    {
        p_Frame=MOUSE_OVER;
        if(HandleInput::GetInstance()->GetMouse(0))
        {
            p_Frame=CLICKED;
            p_callback();
            p_Released=false;
        }
        else if(!HandleInput::GetInstance()->GetMouse(0))
        {
            p_Released=true;
            p_Frame=MOUSE_OVER;
        }
        else
        {
            p_Frame=MOUSE_OUT;
        }
    }
    else p_Frame=MOUSE_OUT;
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}
