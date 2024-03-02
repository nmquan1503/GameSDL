
#include "NPC.h"


/*void drawRound(int x,int y,int h,int w,SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a);
    SDL_Rect rect = {x + 10, y, w - 2 * 10, h};
    SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &rect);

    rect = {x, y + rad, rad, h - 2 * rad};
    SDL_RenderFillRect(renderer, &rect);

    rect = {x + w - rad, y + rad, rad, h - 2 * rad};
    SDL_RenderFillRect(renderer, &rect);

    // Vẽ các điểm góc bo với độ trong suốt
    for (int i = x + rad; i < x + w - rad; ++i) {
        for (int j = y; j < y + h; ++j) {
            // Tính toán độ đồng dạng để làm mịn góc bo và áp dụng độ trong suốt
            double distance = sqrt(pow(i - x - rad, 2) + pow(j - y - rad, 2));
            double alphaFactor = std::min(1.0, distance / rad);
            Uint8 adjustedAlpha = static_cast<Uint8>(alphaFactor * alpha);

            // Áp dụng màu sắc và độ trong suốt
            SDL_SetRenderDrawColor(renderer, rectColor.r, rectColor.g, rectColor.b, adjustedAlpha);
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }



    rad=10,alpha=100;
}

NPC::NPC(int x,int y,int w,int h,std::string TexID,std::string FontID):pos_in_map_x(x),pos_in_map_y(y),p_w(w),p_h(h),p_TexID(TexID),p_FontID(FontID)
{
    text={"Cẩn thận!Hắn đang tới kìa!","Cảm ơn con đã cứu ta."};
    selection={"Đợi con xíu.","Về thôi sư phụ."};
}

void NPC::update()
{
    Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
    if(pos_in_map_x-p_x>=200||pos_in_map_y-p_y<=-200)pointed=false;
    else if(pointed==false && talk==false && vec->GetX()>=p_x&&vec->GetX()<=p_x+p_w&&vec->GetY()>=p_y&&vec->GetY()<=p_y+p_h&&pos_in_map_x-p_x<=200&&pos_in_map_y-p_y>=-200&&HandleInput::GetInstance()->GetMouse(0))
    {
        pointed=true;
    }
    else if(pointed==true&&HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_0))
    {
        talk=true;
    }
    else if(talk==true&&vec->GetX()>p_x+100||vec->GetY()<p_y-100||vec->GetY()>p_y+100)
    {
        pointed=false;
        talk=false;
    }
    /*if(talk==false)
    {
            comment=0;
            commentSize=text[comment].size();
    }
    else if(pointed==true&&HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_RETURN))
    {
        talk=true;
        comment=(++comment)%2;
        commentSize=++commentSize;
        if(commentSize>sizeof(text[comment].c_str()))commentSize=sizeof(text[comment].c_str());
    }*/
  /*  if(pos_in_map_x<=485)
    {
        p_x=0;
    }
    else if(pos_in_map_x>485 &&pos_in_map_x<1505)
    {
        p_x=485-(pos_in_map_x-0);
        //p_pos.SetX(485-(pos_in_map_x-fir_x));
    }
    else
    {
        p_x=0-1020;
        //p_pos.SetX(fir_x-1020);
    }

    if(pos_in_map_y<=262)
    {
        p_y=945;
        //p_pos.SetY(fir_y);
    }
    else if(pos_in_map_y>262&&pos_in_map_y<862)
    {
        p_y=262-(pos_in_map_y-945);
        //p_pos.SetY(262-(pos_in_map_y-fir_y));
    }
    else {
            p_y=945-600;
        //p_pos.SetY(fir_y-600);
    }
    p_Frame=(++p_Frame)%2;
}

void NPC::draw()
{

    ManageTexture::GetInstance()->drawFrame(p_TexID,p_x,p_y,p_w,p_h,p_Frame,Game::GetInstance()->GetRenderer(),flip);
    if(talk==true)
    {
        std::string tmp="";
        for(int i=0;i<commentSize;i++)tmp+=text[comment][i];
        SDL_Color color={0,0,0};
        SDL_Texture* tex=ManageFont::GetInstance()->createTex(p_FontID,tmp,color,Game::GetInstance()->GetRenderer());
        int w;int h;
        SDL_QueryTexture(tex,NULL,NULL,&w,&h);
        int x=(1020-w)/2;
        int y=450;
        SDL_Rect dst ={x,y,w,h};
        SDL_RenderCopy(Game::GetInstance()->GetRenderer(),tex,NULL,&dst);
        commentSize++;
        if(commentSize>sizeof(text[comment].c_str()))commentSize--;
    }
}

void NPC::clean()
{

}

void NPC::handle()
{
    //if(pointed==true&&HandleInput::GetInstance()->HandleInput())
}
*/

NPC::NPC(const LoaderParams* p_Params,void(*callback)(),int x,int y):SDLGameObject(p_Params),p_callback(callback),pos_in_map_x(x),pos_in_map_y(y){}

void NPC::draw()
{
    SDLGameObject::draw();
}

void NPC::clean()
{
    SDLGameObject::clean();
}

void NPC::update()
{
    Vector2D* MousePos=HandleInput::GetInstance()->GetMousePos();
    if(MousePos->GetX()<(p_pos.GetX()+p_w) && MousePos->GetX()>p_pos.GetX() && MousePos->GetY()<(p_pos.GetY()+p_h) && MousePos->GetY()>p_pos.GetY() && HandleInput::GetInstance()->GetMouse(0))
    {
        p_point=true;
        FramePlus=2;
    }
    else if(p_point==true&&HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_RETURN))
    {
        p_callback();
    }
    else if(pos_in_map_x>200||pos_in_map_y<845)
    {
        p_point=false;
        FramePlus=0;
    }
}
