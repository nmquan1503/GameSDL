#ifndef _PlayState_2_h_
#define _PlayState_2_h_

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
#include "Boss.h"

class GameObject;

class PlayState2 : public GameState
{
public:
    PlayState2(GameObject* p):p_player(p){}
    int CollisionPlayer(GameObject* g);
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string GetStateID() const
    {
        return p_Play2ID;
    }
    //int Pos(GameObject* g);
private:
    static std::string p_Play2ID;
    GameObject* p_player;
    GameObject* p_boss;
    std::vector<GameObject*>p_darts;
    std::vector<GameObject*>p_eskill_player;
    std::vector<GameObject*>p_eskill_boss;
    std::vector<GameObject*>p_grass_1;
    std::vector<GameObject*>p_grass_2;
    std::vector<GameObject*>p_grass_3;

    std::map<std::pair<int,int>,int> Pos_Map;
    int numSoldier=0;
};



#endif // _PlayState_2_h_
