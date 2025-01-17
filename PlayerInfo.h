#ifndef _PlayerInfo_h_
#define _PlayerInfo_h_

#include "GameData.h"
#include "MenuButton.h"
#include "GameState.h"
#include "ManageFont.h"
#include "ManageTexture.h"
#include "GameObject.h"
#include "Note.h"
#include "Animation.h"
#include "ManageSound.h"

#include <iostream>
#include <string>
#include <vector>

class Note;

class PlayerInfo : public GameState
{
private:

    bool p_scrolling=false;
    int y_scr=115;

    static int hp_rate;
    static int mana_rate;
    static int dmg_rate;
    static int dart_rate;

    static std::string p_PlInfo;
    static std::vector<GameObject*> p_gameObjects;
    static std::vector<Note*> p_notes;
    static std::vector<GameObject*> p_animation;

    static bool view;
    static SDL_Texture* tex;
    static int frame_player;
    static int row_player;
    static int distance_dart;
public:
    PlayerInfo();

    static void p_upgradeHP();
    static void p_upgradeMana();
    static void p_upgradeDmg();
    static void p_upgradeDart();

    static void p_view();

    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string GetStateID() const {return p_PlInfo;}
};


#endif // _PlayerInfo_h_
