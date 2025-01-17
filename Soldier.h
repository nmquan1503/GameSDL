#ifndef _Soldier_h_
#define _Soldier_h_


#include <iostream>
#include <vector>

#include "GameObject.h"
#include "SDL_GameObject.h"
#include "ManageTexture.h"
#include "Game.h"
#include "ManageFont.h"

class Soldier : public SDLGameObject
{
public:
    Soldier(const LoaderParams* Params,int x_pl,int y_pl,int hp_,int dmg_,int ID);
    virtual void draw();
    virtual void update();
    virtual void clean();
    int GetPosMap(){return p_SoldierPos;}
    int GetPosInMapX(){return p_pos_x;}
    int GetPosInMapY(){return p_pos_y;}
    int GetGrassY1(){return p_grass_y1;}
    void SetSoldierPos(int s){p_SoldierPos=s;}
    void SetPlayerPos(int s){p_PlayerPos=s;}
    void SetMapX(int t){pos_in_map_x=t;}
    void SetMapY(int t){pos_in_map_y=t;}

    bool GetATK(){return p_ATKING;}

    void SetHP(int t){hp=std::max(0,std::min(hp_max,hp+t));}

    int GetHP(){return hp;}
    int GetDmg(){return dmg;}

    //Vector2D GetPos(){return p_pos;}

    void push_hp_lose(int t){hp_lose.push_back(t);}

private:
    int Map_ID;

    int pos_in_map_x=0;
    int pos_in_map_y=0;
    int p_pos_x;
    int p_pos_y;
    int p_SoldierPos;
    int p_PlayerPos;
    int p_grass_x1;
    int p_grass_y1;
    int p_grass_w1;
    int p_grass_x2;
    int p_grass_y2;
    int p_grass_w2;
    bool p_up=false;
    bool p_down=true;
    int timeJump=0;
    int dst_x=0;
    int dst_y=0;
    int dst_w=0;
    int timeMove=0;

    int hp_max;
    int hp;
    int dmg;

    bool p_ATKING=false;

    std::vector<int>hp_lose;
};

#endif // _Soldier_h_
