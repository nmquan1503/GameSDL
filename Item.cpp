
#include "Item.h"
#include "EspFunction.cpp"

int Item::Grass_map1()
{
    if(pos_x+p_w>450&&pos_x<900&&pos_y+p_h<=550)return 550;
    if(pos_x+p_w>350&&pos_x<550&&pos_y+p_h<=650)return 650;
    if(pos_x+p_w>350&&pos_x<550&&pos_y+p_h<=750)return 750;
    if(pos_x+p_w>1000&&pos_x<1335&&pos_y+p_h<=700)return 700;
    if(pos_x+p_w>1480&&pos_x<1680&&pos_y+p_h<=750)return 750;
    if(pos_x+p_w>1790&&pos_y+p_h<=850)return 850;
    if(pos_x+p_w>1335&&pos_x<1395&&pos_y+p_h<=870)return 870;
    if(pos_x+p_w>1395&&pos_x<1455&&pos_y+p_h<=930)return 930;
    if(pos_x+p_w>1455&&pos_x<1515&&pos_y+p_h<=990)return 990;
    if(pos_x+p_w>450&&pos_x<650&&pos_y+p_h<=850)return 850;
    if(pos_x+p_w>750&&pos_x<1000&&pos_y+p_h<=950)return 950;
    if(pos_x+p_w>650&&pos_x<750&&pos_y+p_h<=1050)return 1050;
    if(pos_x<500&&pos_y+p_h<=1050)return 1050;
    if(pos_x+p_w>1515&&pos_y+p_h<=1050)return 1050;
    return 1160;
}

Item::Item(const LoaderParams* Params,int p_x,int p_y,std::string type,int ID):SDLGameObject(Params),pos_in_map_x(p_x),pos_in_map_y(p_y),itemID(type),Map_ID(ID)
{
    pos_x=Params->GetX();
    pos_y=Params->GetY();
    int x,w;
    if(Map_ID==1)
    {
        SetToaDo1(Pos_Map_1(pos_x,pos_y,p_w,p_h),x,p_grass_y,w);
    }
    else if(Map_ID==2)
    {
        SetToaDo2(Pos_Map_2(pos_x,pos_y,p_w,p_h),x,p_grass_y,w);
    }
    else if(Map_ID==3)
    {
        SetToaDo3(Pos_Map_3(pos_x,pos_y,p_w,p_h),x,p_grass_y,w);
    }
}

void Item::update()
{
    if(pos_y+p_h<p_grass_y)pos_y+=std::min(10,p_grass_y-(pos_y+p_h));

    p_Frame=(++p_Frame)%2;
    timeSpell++;

    if(pos_in_map_x<=485)
    {
        p_pos.SetX(pos_x);
    }
    else if(pos_in_map_x>485 &&pos_in_map_x<1505)
    {
        p_pos.SetX(485-(pos_in_map_x-pos_x));
    }
    else
    {
        p_pos.SetX(pos_x-1020);
    }

    if(pos_in_map_y<=262)
    {
        p_pos.SetY(pos_y);
    }
    else if(pos_in_map_y>262&&pos_in_map_y<862)
    {
        p_pos.SetY(262-(pos_in_map_y-pos_y));
    }
    else
    {
        p_pos.SetY(pos_y-600);
    }
}

void Item::draw()
{
    SDLGameObject::draw();
}

void Item::clean()
{
    SDLGameObject::clean();
}
