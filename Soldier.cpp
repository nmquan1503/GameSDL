
#include "Soldier.h"

void SetToaDo(int t,int &x,int &y,int &w)
{
    if(t==1)
    {
        x=0;
        y=1050;
        w=500;
    }
    else if(t==2)
    {
        x=500;
        y=1160;
        w=150;
    }
    else if(t==3)
    {
        x=650;
        y=1050;
        w=100;
    }
    else if(t==4)
    {
        x=750;
        y=950;
        w=250;
    }
    else if(t==5)
    {
        x=1000;
        y=700;
        w=335;
    }
    else if(t==6)
    {
        x=1515;
        y=1050;
        w=525;
    }
    else if(t==7)
    {
        x=450;
        y=850;
        w=200;
    }
    else if(t==8)
    {
        x=1335;
        y=870;
        w=60;
    }
    else if(t==9)
    {
        x=1395;
        y=930;
        w=60;
    }
    else if(t==10)
    {
        x=350;
        y=750;
        w=200;
    }
    else if(t==11)
    {
        x=350;
        y=650;
        w=200;
    }
    else if(t==12)
    {
        x=450;
        y=550;
        w=450;
    }
    else if(t==13)
    {
        x=1480;
        y=750;
        w=200;
    }
    else if(t==14)
    {
        x=1790;
        y=850;
        w=250;
    }
    else
    {
        x=1455;
        y=990;
        w=60;
    }
}

int Posk(int x,int y)
{
    //int x1=static_cast<Player*>(g)->GetPosInMapX(),y1=static_cast<Player*>(g)->GetPosInMapY();
    if(x>390&&x<900&&y+75<=550)return 12;
    if(x>290&&x<550&&y+75<=650)return 11;
    if(x>290&&x<550&&y+75<=750)return 10;
    if(x>940&&x<1335&&y+75<=700)return 5;
    if(x>1420&&x<1680&&y+75<=750)return 13;
    if(x>1730&&y+75<=850)return 14;
    if(x>=1335&&x<1395&&y+75<=870)return 8;
    if(x>=1395&&x<1455&&y+75<=930)return 9;
    if(x>=1455&&x<1515&&y+75<=990)return 15;
    if(x>390&&x<650&&y+75<=850)return 7;
    if(x>690&&x<1000&&y+75<=950)return 4;
    if(x>590&&x<750&&y+75<=1050)return 3;
    if(x<490&&y+75<=1050)return 1;
    if(x>=1515&&y+75<=1050)return 6;
    return 2;
}

Soldier::Soldier(const LoaderParams* Params,int x_pl,int y_pl):SDLGameObject(Params)
{
    pos_in_map_x=x_pl;
    pos_in_map_y=y_pl;
    p_pos_x=Params->GetX();
    p_pos_y=Params->GetY();
    p_SoldierPos=Posk(p_pos_x,p_pos_y);
}



void Soldier::draw()
{
    SDLGameObject::draw();

    int tmp_x=p_pos.GetX()+p_w/2-40;
    int tmp_y=p_pos.GetY()-20;

    SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(),128,128,128,255);
    SDL_Rect dst={tmp_x,tmp_y,80,10};
    SDL_RenderFillRect(Game::GetInstance()->GetRenderer(),&dst);

    SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(),255,0,0,255);
    dst={tmp_x,tmp_y,hp*80/100,10};
    SDL_RenderFillRect(Game::GetInstance()->GetRenderer(),&dst);
}

void Soldier::update()
{
    p_ATKING=false;
    //p_SoldierPos=Posk(p_pos_x,p_pos_y);
    p_SoldierPos=Posk(p_pos_x,p_pos_y);

    SetToaDo(p_PlayerPos,p_grass_x2,p_grass_y2,p_grass_w2);
    SetToaDo(p_SoldierPos,p_grass_x1,p_grass_y1,p_grass_w1);

    if(p_up==true)
    {
        p_Frame=0;
        p_TexID="fide3";
        p_w=55;
        p_h=85;
        if(p_pos_x==dst_x&&p_pos_y==dst_y)
        {
            p_up=false;
            //  p_SoldierPos=p_PlayerPos;
        }
        else
        {
            if(p_pos_y>dst_y)
            {
                p_pos_y-=std::min(10,p_pos_y-dst_y);
            }
            else if(p_pos_x<dst_x)
            {
                flip=true;
                p_pos_x+=std::min(10,dst_x-p_pos_x);
            }
            else if(p_pos_x>dst_x)
            {
                flip=false;
                p_pos_x-=std::min(10,p_pos_x-dst_x);
            }
            else p_pos_y+=std::min(10,dst_y-p_pos_y);
        }
    }

    else if(p_down==true)
    {

        p_TexID="fide4";
        p_h=90;
        p_w=55;
        if(p_pos_y+75==p_grass_y1)p_down=false;
        else     p_pos_y+=std::min(5,p_grass_y1-p_pos_y-75);
    }
    else if((timeMove%10)<=5)
    {

        p_w=80;
        p_h=65;
        p_TexID="fide5";
        p_Frame=(++p_Frame)%2;
        if(p_SoldierPos==p_PlayerPos)
        {
            Vector2D vec=Vector2D(pos_in_map_x-p_pos_x,pos_in_map_y-p_pos_y);
            if(vec.length()<=10)
            {
                p_ATKING=true;
                p_TexID="fide6";
                p_w=95;
                p_h=70;
                if(vec.GetX()>0)flip=true;
                else flip=false;
                p_pos_x+=vec.GetX();
                p_pos_y+=vec.GetY();
            }
            else
            {
                if(pos_in_map_x>p_pos_x)
                {
                    p_pos_x+=std::min(10,pos_in_map_x-p_pos_x);
                    flip=true;
                }
                else
                {
                    p_pos_x+=std::min(-10,-pos_in_map_x+p_pos_x);
                    flip=false;
                }
            }
        }
        else
        {
            if(p_grass_x1>=p_grass_x2&&p_grass_y1>p_grass_y2)
            {
                flip=false;
                int t=std::max(p_grass_x2+p_grass_w2,p_grass_x1);
                if(p_pos_x<=t)
                {
                    dst_x=p_grass_x2+p_grass_w2-60;
                    dst_y=p_grass_y2-75;
                    p_up=true;
                }
                else
                {
                    p_pos_x-=std::min(10,p_pos_x-t);
                }
            }
            else if(p_grass_x1>=p_grass_x2&&p_grass_y1<p_grass_y2)
            {
                flip=false;
                if(p_pos_x==p_grass_x1)
                {
                    dst_x=std::min(p_grass_x2+p_grass_w2-60,p_grass_x1-60);
                    dst_y=p_grass_y2-75;
                    p_up=true;
                }
                else p_pos_x-=std::min(10,p_pos_x-p_grass_x1);
            }
            else if(p_grass_x1<p_grass_x2&&p_grass_y1>p_grass_y2)
            {
                flip=true;
                int t=std::min(p_grass_x1+p_grass_w1-60,p_grass_x2-60);
                if(p_pos_x>=t)
                {
                    p_up=true;
                    dst_x=std::max(p_pos_x,p_grass_x2);
                    dst_y=p_grass_y2-75;
                }
                else
                {
                    p_pos_x+=std::min(10,t-p_pos_x);
                }
            }
            else if(p_grass_x1<p_grass_x2&&p_grass_y1<p_grass_y2)
            {
                flip=true;
                if(p_pos_x>=p_grass_x1+p_grass_w1-60)
                {
                    p_up=true;
                    dst_x=std::max(p_grass_x1+p_grass_w1,p_grass_x2);
                    dst_y=p_grass_y2-75;
                }
                else p_pos_x+=std::min(10,p_grass_x1+p_grass_w1-60);
            }
        }
    }
    else
    {
        p_Frame=0;
        p_TexID="fide1";
        p_w=60;
        p_h=75;
    }
    timeMove=(++timeMove)%1000;



    if(pos_in_map_x<=485)
    {
        p_pos.SetX(p_pos_x);
    }
    else if(pos_in_map_x>485 &&pos_in_map_x<1505)
    {
        p_pos.SetX(485-(pos_in_map_x-p_pos_x));
    }
    else
    {
        p_pos.SetX(p_pos_x-1020);
    }

    if(pos_in_map_y<=262)
    {
        p_pos.SetY(p_pos_y);
    }
    else if(pos_in_map_y>262&&pos_in_map_y<862)
    {
        p_pos.SetY(262-(pos_in_map_y-p_pos_y));
    }
    else
    {
        p_pos.SetY(p_pos_y-600);
    }
}

void Soldier::clean()
{
    ;
}
