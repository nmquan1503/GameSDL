#ifndef _GameOverState_h_
#define _GameOverState_h_

#include "GameState.h"
#include "Game.h"
#include "ManageTexture.h"
#include "HandleInput.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "MenuState.h"
#include "PlayState.h"
#include "ManageFont.h"

#include<iostream>
#include<vector>

class GameObject;

class GameOverState : public GameState
{

private:
    static std::string p_GameOverID;
    std::vector<GameObject*> p_gameObjects;
    static void p_toRestart();
    static void p_toHome();

    std::string p_TexID;
    int p_w,p_h;
    SDL_Texture* p_tex;

    int p_gold;
    int p_gem;
    int p_time;
    int p_score;

    static int Map_ID;

    int t;
public:
    GameOverState(SDL_Texture* tex,std::string texID,int w,int h,int gold,int gem,int score,int time,int ID);
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string GetStateID() const {return p_GameOverID;}
};


#endif // _GameOverState_h_
