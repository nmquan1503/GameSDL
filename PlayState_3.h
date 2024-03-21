#ifndef _PlayerState3_h_
#define _PlayerState3_h_

#include<vector>
#include<iostream>
#include<map>
#include<algorithm>

#include "GameState.h"
#include "GameObject.h"
#include "SDL_GameObject.h"
#include "ManageTexture.h"
#include "Game.h"
#include "PauseState.h"
#include "Grass.h"
#include "GameOverState.h"
#include "Soldier.h"
#include "Boss.h"
#include "ManageFont.h"
#include "ManageSound.h"
#include "Item.h"
#include "GameData.h"
#include "Animation.h"

class PlayState3 : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string GetStateID() const
    {
        return p_Play3ID;
    }
private:

    static std::string p_Play3ID;

    GameObject* p_player;

    std::vector<GameObject*>p_soldiers;
    std::vector<GameObject*>p_boss;
    std::vector<GameObject*>p_darts;
    std::vector<GameObject*>p_eskill_player;
    std::vector<std::vector<GameObject*>>p_eskill_boss;
    std::vector<GameObject*>p_grass_1;
    std::vector<GameObject*>p_grass_2;
    std::vector<GameObject*>p_grass_3;
    std::vector<GameObject*>p_item;

    std::vector<GameObject*>p_animation;

    std::map<std::pair<int,int>,int> Pos_Map;

    int best_score;
    int best_time;

    int p_score=0;
    int p_time=0;
    bool runTime=true;

    Uint32 p_start_loop;

    int count_boss_max=1;
};

#endif // _PlayerState3_h_
