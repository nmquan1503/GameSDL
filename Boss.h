#ifndef _Boss_h_
#define _Boss_h_

#include <vector>
#include <iostream>
#include <string.h>
#include <string>

#include "GameObject.h"
#include "SDL_GameObject.h"
#include "ManageTexture.h"
#include "Game.h"


class Boss : public SDLGameObject
{
public:
    Boss(const LoaderParams* Params,int x_pl,int y_pl);
    virtual void draw();
    virtual void update();
    virtual void clean();

    void update2();
    int GetPosMap(){return p_BossPos;}
    void SetBossPos(int s){p_BossPos=s;}
    void SetPlayerPos(int s){p_PlayerPos=s;}
    void SetMapX(int t){pos_in_map_x=t;}
    void SetMapY(int t){pos_in_map_y=t;}

    bool GetATK(){return p_ATK_nor;}

    void SetHP(int t){hp+=t;}

    int GetHP(){return hp;}

    std::vector<GameObject*> GetEskill(){return p_eskill;}
    void SetEskill(std::vector<GameObject*>es){p_eskill=es;}
    void push_hp_lose(int t){hp_lose.push_back(t);}
private:
    int pos_in_map_x=0;
    int pos_in_map_y=0;
    int p_pos_x;
    int p_pos_y;
    int p_BossPos;
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
    int timeMove=1;

    int hp=10000;
    int mana=200;


    std::vector<GameObject*>p_eskill;
    bool p_ATK_nor=false;
    bool p_ATK_eskill=false;

    std::vector<int>hp_lose;
};

#endif // _Boss_h_
