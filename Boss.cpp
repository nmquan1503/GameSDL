
#include "Boss.h"
#include "EspFunction.cpp"


Boss::Boss(const LoaderParams* Params,int x_pl,int y_pl,int ID):SDLGameObject(Params)
{
    Map_ID=ID;
    pos_in_map_x=x_pl;
    pos_in_map_y=y_pl;
    p_pos_x=Params->GetX();
    p_pos_y=Params->GetY();
    if(ID==2)
        p_BossPos=Pos_Map_2(p_pos_x,p_pos_y,110,150);
    else if(ID==3)
        p_BossPos=Pos_Map_3(p_pos_x,p_pos_y,110,150);
    p_Frame=0;
}



void Boss::draw()
{
    SDLGameObject::draw();

    if(hp>0)
    {


        int tmp_x=p_pos.GetX()+p_w/2-100;
        int tmp_y=p_pos.GetY()-30;

        SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(),128,128,128,255);
        SDL_Rect dst= {tmp_x,tmp_y,200,20};
        SDL_RenderFillRect(Game::GetInstance()->GetRenderer(),&dst);

        SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(),255,0,0,255);
        dst= {tmp_x,tmp_y,std::max(0,hp*200)/10000,20};
        SDL_RenderFillRect(Game::GetInstance()->GetRenderer(),&dst);



        for(int i:hp_lose)
        {
            std::string tmp=std::to_string(i);
            int t1=rand()%20-10;
            int t2=rand()%8-4;
            ManageFont::GetInstance()->drawTextBlended("font1",tmp, {255,255,0,255},p_pos.GetX()+p_w/2+t1,p_pos.GetY()-20+t2,Game::GetInstance()->GetRenderer());
        }
        hp_lose.clear();
    }


}

void Boss::update2()
{
    p_TexID="boss_die";
    p_Frame=0;
    p_w=140;
    p_h=100;
    p_pos_y+=std::max(0,p_grass_y1-(p_pos_y+60));
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

void Boss::update()
{

    int speed=rand()%5+8;


    p_ATK_nor=false;

    for(int i=0; i<p_eskill.size(); i++)
    {
        if(static_cast<Eskill*>(p_eskill[i])->GetTime()==8)
        {
            p_eskill.erase(p_eskill.begin()+i);
            i--;
        }
    }

    if(Map_ID==2)
        p_BossPos=Pos_Map_2(p_pos_x,p_pos_y,110,150);
    else if(Map_ID==3)
        p_BossPos=Pos_Map_3(p_pos_x,p_pos_y,110,150);

    if(Map_ID==2)
    {
        SetToaDo2(p_PlayerPos,p_grass_x2,p_grass_y2,p_grass_w2);
        SetToaDo2(p_BossPos,p_grass_x1,p_grass_y1,p_grass_w1);
    }
    else
    {
        SetToaDo3(p_PlayerPos,p_grass_x2,p_grass_y2,p_grass_w2);
        SetToaDo3(p_BossPos,p_grass_x1,p_grass_y1,p_grass_w1);
    }


    Vector2D vec=Vector2D(pos_in_map_x-p_pos_x,pos_in_map_y-p_pos_y);
    Vector2D vec2=Vector2D(pos_in_map_x,pos_in_map_y);


    //attack = eskill
    if(mana>=100&&vec.length()<=600&&timeMove%100==0)
    {
        ManageSound::GetInstance()->playSound("eskill1",0);
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



    //move next grass
    else if(p_up==true)
    {
        p_TexID="boss_jumpup";
        p_Frame=0;
        p_w=110;
        p_h=150;
        if(p_pos_x==dst_x&&p_pos_y==dst_y)
        {
            p_up=false;
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
            else
            {
                p_pos_y+=std::min(10,dst_y-p_pos_y);
            }
        }
    }
    else if((timeMove%10<=10))
    {



        //attack
        if(p_BossPos==p_PlayerPos)
        {
            if((Vector2D(p_pos_x+100,p_pos_y+115)-vec2).length()<=50&&mana>=5)
            {

                p_TexID="boss_atk_nor";
                p_Frame=(++p_Frame)%5;
                p_w=250;
                p_h=190;
                if(p_pos_x+100>pos_in_map_x)flip=false;
                else flip=true;
                if(timeMove%5==0)
                {
                    ManageSound::GetInstance()->playSound("boss_atk_nor",0);
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
                if(p_pos_x<pos_in_map_x-120)
                {
                    p_pos_x+=std::min(speed,pos_in_map_x-120-p_pos_x);
                    flip=true;
                }
                else if(p_pos_x>pos_in_map_x-70)
                {
                    flip=false;
                    p_pos_x-=std::min(speed,p_pos_x-(pos_in_map_x-70));
                }
            }
        }



        //move
        else
        {
            p_TexID="boss_run";
            p_w=150;
            p_h=150;
            p_Frame=(++p_Frame)%3;

            if(p_grass_y1>p_grass_y2)
            {
                if(p_grass_x1<p_grass_x2&&p_grass_x1+p_grass_w1>p_grass_x2+p_grass_w2)
                {
                    if(p_pos_x>=p_grass_x2-110&&p_pos_x<=p_grass_x2+p_grass_w2)
                    {
                        p_up=true;
                        dst_y=p_grass_y2-150;
                        dst_x=std::min(std::max(p_pos_x,p_grass_x2),p_grass_x2+p_grass_w2-110);
                    }
                    else if(p_pos_x<p_grass_x2-110)
                    {
                        p_pos_x+=std::min(speed,p_grass_x2-110-p_pos_x);
                        flip=true;
                    }
                    else
                    {
                        p_pos_x-=std::min(speed,p_pos_x-p_grass_x2-p_grass_w2);
                        flip=false;
                    }
                }
                else if(p_grass_x1<p_grass_x2)
                {
                    if(p_pos_x>=std::min(p_grass_x1+p_grass_w1-110,p_grass_x2-110))
                    {
                        p_up=true;
                        dst_y=p_grass_y2-150;
                        dst_x=std::max(p_pos_x,p_grass_x2);
                    }
                    else
                    {
                        flip=true;
                        p_pos_x+=std::min(speed,std::min(p_grass_x2,p_grass_x1+p_grass_w1)-110-p_pos_x);
                    }
                }
                else
                {
                    if(p_pos_x<=std::max(p_grass_x2+p_grass_w2,p_grass_x1))
                    {
                        p_up=true;
                        dst_y=p_grass_y2-150;
                        dst_x=std::min(p_pos_x,p_grass_x2+p_grass_w2-110);
                    }
                    else
                    {
                        flip=false;
                        p_pos_x-=std::min(speed,std::max(p_grass_x2+p_grass_w2,p_grass_x1));
                    }
                }
            }
            else
            {
                if(p_grass_x1>=p_grass_x2)
                {
                    flip=false;
                    if(p_pos_x<=p_grass_x1)
                    {
                        p_up=true;
                        dst_x=std::min(p_grass_x1-110,p_grass_x2+p_grass_w2-110);
                        dst_y=p_grass_y2-150;
                    }
                    else p_pos_x-=std::min(speed,p_pos_x-p_grass_x1);
                }
                else
                {
                    flip=true;
                    if(p_pos_x>=p_grass_x1+p_grass_w1-110)
                    {
                        dst_x=std::max(p_grass_x1+p_grass_w1,p_grass_x2);
                        dst_y=p_grass_y2-150;
                        p_up=true;
                    }
                    else p_pos_x+=std::min(speed,p_grass_x1+p_grass_w1-110-p_pos_x);
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




    //render setting
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
    SDLGameObject::clean();
    for(GameObject* i:p_eskill)
        i->clean();
    p_eskill.clear();

    hp_lose.clear();
}
