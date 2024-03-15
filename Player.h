#ifndef _Player_
#define _Player_

#include <iostream>
#include <vector>

#include "GameObject.h"
#include "SDL_GameObject.h"
#include "HandleInput.h"
#include "Vector2D.h"
#include "PlayState.h"
#include "dart.h"
#include "Eskill.h"
#include "Grass.h"
#include "ManageTexture.h"
#include "ManageFont.h"
#include "ManageSound.h"
#include "GameData.h"
#include "SpItem.h"

class Player : public SDLGameObject
{
public:
    Player(const LoaderParams* p_Params);
    virtual void draw();
    virtual void update();
    virtual void clean();
    std::vector<GameObject*> GetDarts(){return p_Darts;}
    std::vector<GameObject*> GetEskill(){return p_Eskill;}
    void SetPosInMapX(int x){pos_in_map_x=x;}
    void SetPosInMapY(int y){pos_in_map_y=y;}
    int GetPosInMapX(){return pos_in_map_x;}
    int GetPosInMapY(){return pos_in_map_y;}
    void turnLeft();
    void turnRight();
    void goUp();
    void goDown();
    void fixDown(int view);
   // void fixRight(int view);
    //void fixLeft(int view);

    bool GetJumped(){return p_Jumped;}
    void SetJumped(bool j){p_Jumped=j;}
    int GetTimeJump(){return (timeJump+1)*(timeJump+1);}
    void SetTimeJump(int t){timeJump=t;}

    void SetDownCan(int d){p_down_can=d;}
    void SetRightCan(int r){p_right_can=r;}
    void SetLeftCan(int l){p_left_can=l;}

    void SetHP(int t){hp=std::max(0,std::min(hp_max,hp+t));}
    void SetMana(int t){mana=std::max(0,std::min(mana_max,mana+t));}
    int GetHP(){return hp;}
    int GetDamage(){return damage;}
    int GetSpeed(){return speed;}

    void SetDart(std::vector<GameObject*> Dart){p_Darts=Dart;}
    int GetTimeDie(){return timeDie;}


    void push_hp_lose(int t){hp_lose.push_back(t);}

    void SetGold(int g){gold+=g;}
    void SetGem(int g){gem+=g;}
private:
    bool p_IsJump=false;
    bool p_Jumped=false;
    bool p_fly=false;
    int timeJump=0;
    void handle();
    std::vector<GameObject*>p_Darts;
    std::vector<GameObject*>p_Eskill;
    int pos_in_map_x=0;
    int pos_in_map_y=0;
    int p_right_can=15;
    int p_left_can=15;
    int p_down_can=120;

    int hp_max;
    int mana_max;
    int hp;
    int mana;
    int damage;
    int speed;
    int timeDie=0;

    int gold=0;
    int gem=0;
    int hp_spell;
    int mana_spell;
    int damage_spell;
    int hp_x2;
    int mana_x2;
    int speed_spell;

    std::vector<int> hp_lose;
    std::vector<GameObject*>p_sp_item;
};

#endif // _Player_
