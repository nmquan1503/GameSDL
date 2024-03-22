
#include "Soldier.h"
#include "EspFunction.cpp"


Soldier::Soldier(const LoaderParams* Params,int x_pl,int y_pl,int hp_,int dmg_,int ID):SDLGameObject(Params),hp_max(hp_),dmg(dmg_)
{
    Map_ID=ID;
    hp=hp_max;

    pos_in_map_x=x_pl;
    pos_in_map_y=y_pl;
    p_pos_x=p_pos.GetX();
    p_pos_y=p_pos.GetY();
    if(ID==1)
        p_SoldierPos=Pos_Map_1(p_pos_x,p_pos_y,60,75);
    else if(ID==3)
        p_SoldierPos=Pos_Map_3(p_pos_x,p_pos_y,60,75);
}



void Soldier::draw()
{
    SDLGameObject::draw();

    int tmp_x=p_pos.GetX()+p_w/2-40;
    int tmp_y=p_pos.GetY()-20;

    SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(),128,128,128,255);
    SDL_Rect dst= {tmp_x,tmp_y,80,10};
    SDL_RenderFillRect(Game::GetInstance()->GetRenderer(),&dst);

    SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(),255,0,0,255);
    dst= {tmp_x,tmp_y,hp*80/hp_max,10};
    SDL_RenderFillRect(Game::GetInstance()->GetRenderer(),&dst);


    for(int i:hp_lose)
    {
        std::string tmp=std::to_string(i);
        int t1=rand()%20-10;
        int t2=rand()%8-4;
        ManageFont::GetInstance()->drawTextBlended("font1",tmp, {255,255,0,255},p_pos.GetX()+p_w/2+t1,p_pos.GetY()-15+t2,Game::GetInstance()->GetRenderer());
    }
    hp_lose.clear();
}

void Soldier::update()
{
    int speed=rand()%5+7;
    p_ATKING=false;

    if(Map_ID==1)
        p_SoldierPos=Pos_Map_1(p_pos_x,p_pos_y,60,75);
    else if(Map_ID==3)
        p_SoldierPos=Pos_Map_3(p_pos_x,p_pos_y,60,75);

    if(Map_ID==1)
    {

        SetToaDo1(p_PlayerPos,p_grass_x2,p_grass_y2,p_grass_w2);
        SetToaDo1(p_SoldierPos,p_grass_x1,p_grass_y1,p_grass_w1);
    }
    else
    {
        SetToaDo3(p_PlayerPos,p_grass_x2,p_grass_y2,p_grass_w2);
        SetToaDo3(p_SoldierPos,p_grass_x1,p_grass_y1,p_grass_w1);
    }




    if(p_up==true)
    {
        p_Frame=0;
        p_TexID="fide3";
        p_w=55;
        p_h=85;
        if(p_pos_x==dst_x&&p_pos_y==dst_y)
        {
            p_up=false;
        }
        else
        {
            if(p_pos_y>dst_y)
            {
                p_pos_y-=std::min(speed,p_pos_y-dst_y);
            }
            else if(p_pos_x<dst_x)
            {
                flip=true;

                p_pos_x+=std::min(speed,dst_x-p_pos_x);
            }
            else if(p_pos_x>dst_x)
            {
                flip=false;

                p_pos_x-=std::min(speed,p_pos_x-dst_x);
            }
            else
            {

                p_pos_y+=std::min(speed,dst_y-p_pos_y);
            }
        }
    }



    else if(p_down==true)
    {

        p_TexID="fide4";
        p_h=90;
        p_w=55;
        if(p_pos_y+75==p_grass_y1)p_down=false;
        else     p_pos_y+=std::min(speed,p_grass_y1-p_pos_y-75);
    }




    else if((timeMove%10)<=5)
    {

        p_w=80;
        p_h=65;
        p_TexID="fide5";
        p_Frame=(++p_Frame)%2;



        //attack
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
                    p_pos_x+=std::min(speed,pos_in_map_x-p_pos_x);
                    flip=true;
                }
                else
                {
                    p_pos_x+=std::min(-speed,-pos_in_map_x+p_pos_x);
                    flip=false;
                }
            }
        }




        //move
        else
        {
            if(p_grass_y1>p_grass_y2)
            {
                if(p_grass_x1<p_grass_x2&&p_grass_x1+p_grass_w1>p_grass_x2+p_grass_w2)
                {
                    if(p_pos_x>=p_grass_x2-60&&p_pos_x<=p_grass_x2+p_grass_w2)
                    {
                        p_up=true;
                        dst_y=p_grass_y2-75;
                        dst_x=std::min(std::max(p_pos_x,p_grass_x2),p_grass_x2+p_grass_w2-110);
                    }
                    else if(p_pos_x<p_grass_x2-60)
                    {
                        p_pos_x+=std::min(speed,p_grass_x2-60-p_pos_x);
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
                    if(p_pos_x>=std::min(p_grass_x1+p_grass_w1-60,p_grass_x2-60))
                    {
                        p_up=true;
                        dst_y=p_grass_y2-75;
                        dst_x=std::max(p_pos_x,p_grass_x2);
                    }
                    else
                    {
                        flip=true;
                        p_pos_x+=std::min(speed,std::min(p_grass_x2,p_grass_x1+p_grass_w1)-60-p_pos_x);
                    }
                }
                else
                {
                    if(p_pos_x<=std::max(p_grass_x2+p_grass_w2,p_grass_x1))
                    {
                        p_up=true;
                        dst_y=p_grass_y2-75;
                        dst_x=std::min(p_pos_x,p_grass_x2+p_grass_w2-60);
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
                        dst_x=std::min(p_grass_x1-60,p_grass_x2+p_grass_w2-60);
                        dst_y=p_grass_y2-75;
                    }
                    else p_pos_x-=std::min(speed,p_pos_x-p_grass_x1);
                }
                else
                {
                    flip=true;
                    if(p_pos_x>=p_grass_x1+p_grass_w1-60)
                    {
                        dst_x=std::max(p_grass_x1+p_grass_w1,p_grass_x2);
                        dst_y=p_grass_y2-75;
                        p_up=true;
                    }
                    else p_pos_x+=std::min(speed,p_grass_x1+p_grass_w1-60-p_pos_x);
                }
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




    //render
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
    SDLGameObject::clean();
    hp_lose.clear();
}
