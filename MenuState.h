#ifndef _MenuState_h_
#define _MenuState_h_

#include "GameState.h"
#include "GameObject.h"
#include "ManageTexture.h"
#include "Game.h"
#include "MenuButton.h"
#include "OptionsState.h"
#include "InstructionState.h"
#include "ShopState.h"
#include "PlayerInfo.h"
#include "PlayState_3.h"
#include "SDL_GameObject.h"
#include "MenuBG.h"

#include <vector>
#include <iostream>

class SDLGameObject;

class MenuState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string GetStateID() const {return p_MenuID;}
private:
    static std::string p_MenuID;
    static std::vector<GameObject*>p_gameObjects;
    static void p_menuToPlay();
    static void p_exitFromMenu();
    static void p_menuToOptions();
    static void p_menuToInstruction();
    static void p_menuToShop();
    static void p_menuToUpgrade();
    static void p_menuToMap1();
    static void p_menuToMap3();
    static void p_quit();
    static void p_backMenu();

    static bool play;
    static bool quit;
};


#endif // _MenuState_h_
