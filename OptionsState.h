#ifndef _OptionsState_h_
#define _OptionsState_h_

#include<vector>
#include<iostream>

#include "GameState.h"
#include "GameObject.h"
#include "SDL_GameObject.h"
#include "ManageTexture.h"
#include "Game.h"
#include "Vector2D.h"
#include "HandleInput.h"

class GameObject;

class OptionsState : public GameState
{
public:
    OptionsState(GameObject* p_g);
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string GetStateID()const
    {
        return p_OptionsID;
    }
private:
    bool sfx_fix=false;
    bool music_fix=false;
    static std::string p_OptionsID;
    std::vector<GameObject*> p_gameObjects;

};

#endif // _OptionsState_h_
