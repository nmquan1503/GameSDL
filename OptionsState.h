#ifndef _OptionsState_h_
#define _OptionsState_h_

#include<vector>
#include<iostream>

#include "GameState.h"
#include "GameObject.h"
#include "SDL_GameObject.h"
#include "ManageTexture.h"
#include "Game.h"

class GameObject;

class OptionsState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string GetStateID()const {return p_OptionsID;}
private:
    static std::string p_OptionsID;
    std::vector<GameObject*> p_gameObjects;

};

#endif // _OptionsState_h_
