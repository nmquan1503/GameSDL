#ifndef _PlayState_h_
#define _PlayState_h_

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
#include "PlayState_2.h"

class GameObject;

class PlayState : public GameState
{
public:
    int CollisionPlayer(GameObject* g);
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string GetStateID() const
    {
        return p_PlayID;
    }
    //int Pos(GameObject* g);
private:
    static std::string p_PlayID;
    GameObject* p_player;
    std::vector<GameObject*>p_soldiers;
    std::vector<GameObject*>p_darts;
    std::vector<GameObject*>p_eskill;
    std::vector<GameObject*>p_grass_1;
    std::vector<GameObject*>p_grass_2;
    std::vector<GameObject*>p_grass_3;

    std::map<std::pair<int,int>,int> Pos_Map;
    int numSoldier=0;
};


#endif // _PlayState_h_
