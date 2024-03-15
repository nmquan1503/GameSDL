#ifndef _PlayerInfo_h_
#define _PlayerInfo_h_

#include "GameData.h"
#include "MenuButton.h"
#include "GameState.h"
#include "ManageFont.h"
#include "ManageTexture.h"
#include "GameObject.h"
#include "Note.h"

#include <iostream>
#include <string>
#include <vector>

class Note;

class PlayerInfo : public GameState
{
private:

    bool p_scrolling=false;
    int y_scr=15;

    static int hp_rate;
    static int mana_rate;
    static int dmg_rate;
    static int dart_rate;

    static std::string p_PlInfo;
    std::vector<GameObject*> p_gameObjects;
    static std::vector<Note*> p_notes;
public:
    PlayerInfo();

    static void p_upgradeHP();
    static void p_upgradeMana();
    static void p_upgradeDmg();
    static void p_upgradeDart();

    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string GetStateID() const {return p_PlInfo;}
};


#endif // _PlayerInfo_h_
