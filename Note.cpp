#include "Note.h"

Note::Note(std::string id,std::string text,int x_mid,int y,int w_max,SDL_Color color)
{
    p_tex=ManageFont::GetInstance()->createTex(id,text,color,Game::GetInstance()->GetRenderer());
    SDL_QueryTexture(p_tex,NULL,NULL,&p_w,&p_h);
    p_x=x_mid-p_w/2;
    p_y=y;
    p_color=color;
}

void Note::update()
{
    time++;
    if(time<=4)
    {
        p_y-=30;
    }
}

void Note::draw()
{
    SDL_Rect dst={p_x,p_y,p_w,p_h};
    SDL_RenderCopy(Game::GetInstance()->GetRenderer(),p_tex,NULL,&dst);
}

void Note::clean()
{
    SDL_DestroyTexture(p_tex);
}
