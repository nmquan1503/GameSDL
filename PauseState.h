#ifndef _PauseState_h_
#define _PauseState_h_

#include "GameObject.h"
#include "GameState.h"
#include "Game.h"
#include "ManageTexture.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "MenuState.h"
#include "HandleInput.h"
#include "OptionsState.h"

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameObject;

class PauseState : public GameState
{
private:
    static std::string p_PauseID;
    static void p_pauseToResume();
    static void p_pauseToHome();
    static void p_pauseToRestart();
    static void p_pauseToOptions();

    std::vector<GameObject* >p_gameObjects;

    static SDL_Texture* p_tex;

    static int Map_ID;

    static int p_gold;
    static int p_gem;
    static int p_time;
    static int p_score;
    static int p_hp_spell;
    static int p_mana_spell;
    static int p_speed_spell;
    static int p_dmg_spell;
    static int p_hp_x2;
    static int p_mana_x2;

    static bool loading;
    GameObject* load;

public:
    PauseState(SDL_Texture* tex,int ID,int gold,int gem,int time,int score,
                                int hp_spell,int mana_spell,int speed_spell,
                                int dmg_spell,int hp_x2,int mana_x2);

    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string GetStateID() const {return p_PauseID;}
};

#endif // _PauseState_h_
