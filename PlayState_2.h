#ifndef _PlayState_2_h_
#define _PlayState_2_h_

#include<vector>
#include<iostream>
#include<map>
#include<algorithm>
#include <string>

#include "GameState.h"
#include "GameObject.h"
#include "SDL_GameObject.h"
#include "ManageTexture.h"
#include "Game.h"
#include "PauseState.h"
#include "Grass.h"
#include "GameOverState.h"
#include "Boss.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "Animation.h"

class GameObject;
//class NPC;

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


private:

    bool win=false;
    int timeWin=0;

    bool p_start=false;
    bool p_end=false;
    bool IsTalking1=false;
    bool IsTalking2=false;

    static std::string p_Play2ID;
   GameObject* p_player;
    GameObject* p_boss;

    std::string text1="Careful! He's coming!";
    std::string text2="Thank you for saving me.";
    int longText=0;



    std::vector<GameObject*>p_darts;
    std::vector<GameObject*>p_eskill_player;
    std::vector<GameObject*>p_eskill_boss;
    std::vector<GameObject*>p_grass_1;
    std::vector<GameObject*>p_grass_2;
    std::vector<GameObject*>p_grass_3;
    std::vector<GameObject*>p_animation;

    std::map<std::pair<int,int>,int> Pos_Map;
    int numSoldier=0;
};



#endif // _PlayState_2_h_
