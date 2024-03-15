#ifndef _Game_
#define _Game_

#include<iostream>
#include<vector>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>

#include "ManageTexture.h"
#include "GameObject.h"
#include "Player.h"
#include "Soldier.h"
#include "HandleInput.h"
#include "GameState.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "GameData.h"

class Game
{
private:
    bool p_Running;
    SDL_Window* p_window;
    SDL_Renderer* p_renderer;

    ManageTexture* MTex;

    std::vector<GameObject*>GameObjects;
    Game();
    static Game* Instance;
    GameStateMachine* p_GameStateMachine;
   // GameData* data;
public:
    static Game* GetInstance();

    ~Game();
    bool init(const char* title,int width,int height);
    void clean();
    void handleEvents();
    void update();
    void render();
    void quit();
    bool IsRunning(){return p_Running;}
    SDL_Renderer* GetRenderer() const {return p_renderer;}
    GameStateMachine* GetGameStateMachine(){return p_GameStateMachine;}
   // GameData* GetData(){return data;}

};

#endif // _Game_



