#ifndef _ShopState_h_
#define _ShopState_h_

#include "GameData.h"
#include "GameState.h"
#include "MenuButton.h"
#include "ManageTexture.h"
#include "Game.h"
#include "GameObject.h"
#include "SDL_GameObject.h"
#include "Vector2D.h"
#include "HandleInput.h"
#include "Note.h"

#include <vector>
#include <iostream>

class Note;

class ShopState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string GetStateID() const {return p_ShopID;}
private:
    static std::string p_ShopID;
    static std::vector<GameObject*>p_gameObjects;

    bool p_scrolling=false;
    int y_scr=15;

    static void p_buyHP();
    static void p_buyMANA();
    static void p_buyDamage();
    static void p_buyHpX2();
    static void p_buyManaX2();
    static void p_buySpeed();

    static std::vector<Note*>p_notes;
};

#endif // _ShopState_h_
