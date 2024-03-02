

#include "Boss.h"

void SetToaDo2(int t,int &x,int &y,int &w)
{
    if(t==1)
    {
        x=0;
        y=1050;
        w=750;
    }
    else if(t==7)
    {
        x=750;
        y=1050;
        w=490;
    }
    else if(t==2)
    {
        x=450;
        y=920;
        w=600;
    }
    else if(t==3)
    {
        x=1240;
        y=950;
        w=200;
    }
    else if(t==4)
    {
        x=1440;
        y=850;
        w=200;
    }
    else if(t==5)
    {
        x=1640;
        y=750;
        w=200;
    }
    else if(t==6)
    {
        x=1840;
        y=650;
        w=200;
    }
}

int Posk2(int x,int y)
{
    //int x1=static_cast<Player*>(g)->GetPosInMapX(),y1=static_cast<Player*>(g)->GetPosInMapY();
    if(x+110>450&&x<1050&&y+150<=920)return 2;
    if(x+110>1840&&y+150<=650)return 6;
    if(x+110>1640&&x<1840&&y+150<=750)return 5;
    if(x+110>1440&&x<1640&&y+150<=850)return 4;
    if(x+110>1240&&x<1440&&y+150<=950)return 3;
    if(x+110>750&&x<1240&&y+150<=1050)return 7;
    return 1;
}

Boss::Boss(const LoaderParams* Params,int x_pl,int y_pl):SDLGameObject(Params)
{
    pos_in_map_x=x_pl;
    pos_in_map_y=y_pl;
    p_pos_x=Params->GetX();
    p_pos_y=Params->GetY();
    p_BossPos=Posk2(p_pos_x,p_pos_y);
}



void Boss::draw()
{
    SDLGameObject::draw();

    int tmp_x=p_pos.GetX()+p_w/2-100;
    int tmp_y=p_pos.GetY()-30;

    SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(),128,128,128,255);
    SDL_Rect dst={tmp_x,tmp_y,200,20};
    SDL_RenderFillRect(Game::GetInstance()->GetRenderer(),&dst);

    SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(),255,0,0,255);
    dst={tmp_x,tmp_y,std::max(0,hp*200)/10000,20};
    SDL_RenderFillRect(Game::GetInstance()->GetRenderer(),&dst);
}

void Boss::update()
{
    p_ATK_nor=false;

    for(int i=0; i<p_eskill.size(); i++)
    {
        if(static_cast<Eskill*>(p_eskill[i])->GetTime()==8)
        {
            p_eskill.erase(p_eskill.begin()+i);
            i--;
        }
    }

    std::cout<<p_pos_x<<" "<<p_pos_y<<std::endl;
    p_BossPos=Posk2(p_pos_x,p_pos_y);

    SetToaDo2(p_PlayerPos,p_grass_x2,p_grass_y2,p_grass_w2);
    SetToaDo2(p_BossPos,p_grass_x1,p_grass_y1,p_grass_w1);


    Vector2D vec=Vector2D(pos_in_map_x-p_pos_x,pos_in_map_y-p_pos_y);
    Vector2D vec2=Vector2D(pos_in_map_x,pos_in_map_y);
    if(mana>=100&&vec.length()<=600&&timeMove%100==0)
    {
        p_ATK_eskill=true;
        p_TexID="boss_atk_eskill";
        p_Frame=(++p_Frame)%2;
        if(vec.GetX()>=0)
        {
            flip=true;
            p_eskill.push_back(new Eskill(new LoaderParams(p_pos.GetX()+100,p_pos.GetY()-25,200,200,"eskill2"),Vector2D(p_pos_x,p_pos_y),vec2,true));
        }
        else
        {
            flip=false;
            p_eskill.push_back(new Eskill(new LoaderParams(p_pos.GetX(),p_pos.GetY()-25,200,200,"eskill2"),Vector2D(p_pos_x,p_pos_y),vec2,false));
        }
        mana-=100;
    }
    else if(p_down==true)
    {
        p_TexID="boss_jumpdown";
        p_w=110;
        p_h=150;
        p_Frame=0;
        p_pos_y+=std::min(10,p_grass_y1-(p_pos_y+150));
        if(p_pos_y+150==p_grass_y1)
        {
            p_down=false;
        }
    }
    else if(p_up==true)
    {
        p_TexID="boss_jumpup";
        p_Frame=0;
        p_w=110;
        p_h=150;
        if(p_pos_x==dst_x&&p_pos_y==dst_y)
        {
            p_up=false;
            p_BossPos=p_PlayerPos;
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
    else if((timeMove%10<=10))
    {
        if(p_BossPos==p_PlayerPos)
        {
            if(vec.length()<100&&mana>=5)
            {
                p_ATK_nor=true;
                p_TexID="boss_atk_nor";
                p_Frame=(++p_Frame)%5;
                p_w=250;
                p_h=190;
                if(vec.GetX()>=0)flip=true;
                else flip=false;
                // p_pos_x+=vec.GetX();
                //if(vec.GetY()>=0)p_pos_y+=vec.GetY();
                //if(p_pos_y+150>p_grass_y1)p_down=true;
                if(timeMove%5==0)
                {
                    p_ATK_nor=true;
                    mana-=5;
                }
            }
            else
            {

                p_TexID="boss_run";
                p_w=150;
                p_h=150;
                p_Frame=(++p_Frame)%3;
                if(pos_in_map_x-50>p_pos_x)
                {
                    p_pos_x+=std::min(10,pos_in_map_x-50-p_pos_x);
                    flip=true;
                }
                else if(p_pos_x-pos_in_map_x>=50)
                {
                    p_pos_x+=std::max(-10,+pos_in_map_x+50-p_pos_x);
                    flip=false;
                }
            }
        }

        else
        {
            p_TexID="boss_run";
            p_w=150;
            p_h=150;
            p_Frame=(++p_Frame)%3;
            if(p_grass_y1>p_grass_y2)
            {
                int t1=std::max(p_grass_x1,p_grass_x2)-110;
                int t2=std::min(p_grass_x1+p_grass_w1,p_grass_x2+p_grass_w2);
                if(p_pos_x<t1)
                {
                    p_pos_x+=std::min(10,t1-p_pos_x);
                    flip=true;
                }
                else if(p_pos_x>t2)
                {
                    flip=false;
                    p_pos_x-=std::min(10,p_pos_x-t2);
                }
                else
                {
                    dst_x=std::min(std::max(p_pos_x,t1+110),t2-110);
                    dst_y=p_grass_y2-150;
                    p_up=true;
                }

            }
            else
            {
                if(p_grass_x1>=p_grass_x2)
                {
                    flip=false;
                    if(p_pos_x==p_grass_x1)
                    {
                        p_up=true;
                        dst_x=p_pos_x-110;
                        dst_y=p_grass_y2-150;
                    }
                    else p_pos_x-=std::min(10,p_pos_x-p_grass_x1);
                }
                else
                {
                    flip=true;
                    if(p_pos_x==p_grass_x1+p_grass_w1-110)
                    {
                        dst_x=p_grass_x2;
                        dst_y=p_grass_y2-150;
                        p_up=true;
                    }
                    else p_pos_x+=std::min(10,p_grass_x1+p_grass_w1-110-p_pos_x);

                }
            }
        }
    }
    else
    {
        p_TexID="boss_nor";
        p_w=110;
        p_h=150;
        p_Frame=(++p_Frame)%2;
    }


    timeMove=(++timeMove)%1000;
    mana=std::min(++mana,200);
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

void Boss::clean()
{
    ;
}
