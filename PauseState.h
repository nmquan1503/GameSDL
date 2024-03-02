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
    static void p_Pause();
    static void p_pauseToResume();
    static void p_pauseToHome();
    static void p_pauseToRestart();
    static void p_pauseToOptions();

    std::vector<GameObject* >p_gameObjects;

    SDL_Texture* p_tex;
public:
    PauseState(SDL_Texture* tex);

    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string GetStateID() const {return p_PauseID;}
};

#endif // _PauseState_h_
