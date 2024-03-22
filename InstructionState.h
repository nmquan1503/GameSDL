#ifndef _InstructionState_h_
#define _InstructionState_h_

#include "GameState.h"
#include "GameObject.h"
#include "ManageTexture.h"
#include "Game.h"
#include "MenuButton.h"

#include <vector>
#include <iostream>

class InstructionState : public GameState
{
private:
    static std::string p_InsID;
    std::vector<GameObject*>p_gameObjects;

    bool p_scrolling=false;
    int y_scr=115;
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string GetStateID() const {return p_InsID;}
};

#endif // _InstructionState_h_
