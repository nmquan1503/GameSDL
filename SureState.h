#ifndef _SureState_h_
#define _SureState_h_

#include "GameState.h"
#include "GameObject.h"
#include "ManageTexture.h"
#include "Game.h"
#include "MenuButton.h"
#include "OptionsState.h"
#include "MenuBG.h"

#include <vector>
#include <iostream>

class SureState : public GameState
{
private:
    static std::string p_SureID;
    std::vector<GameObject*>p_gameObjects;
    static void p_backMenu();
    static void p_exit();
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string GetStateID() const {return p_SureID;}
};



#endif // _SureState_h_
