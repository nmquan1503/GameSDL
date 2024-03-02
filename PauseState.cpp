
#include "PauseState.h"

std::string PauseState::p_PauseID="PAUSE";

PauseState::PauseState(SDL_Texture* tex):p_tex(tex){}

void PauseState::p_Pause()
{
    Game::GetInstance()->GetGameStateMachine()->changeState(new MenuState());
}

void PauseState::p_pauseToResume()
{
    Game::GetInstance()->GetGameStateMachine()->popState();
}

void PauseState::p_pauseToHome()
{
    Game::GetInstance()->GetGameStateMachine()->changeState(new MenuState());
}

void PauseState::p_pauseToRestart()
{
    Game::GetInstance()->GetGameStateMachine()->changeState(new PlayState());
}

void PauseState::p_pauseToOptions()
{
    Game::GetInstance()->GetGameStateMachine()->changeState(new OptionsState());
}

void PauseState::update()
{
    for(GameObject* i:p_gameObjects)
        i->update();
}

void PauseState::render()
{
    //p_gameObjects[0]->draw();
    SDL_RenderCopy(Game::GetInstance()->GetRenderer(),p_tex,NULL,NULL);
    ManageTexture::GetInstance()->draw("pause",0,0,1020,600,Game::GetInstance()->GetRenderer(),true);
    for(GameObject* i:p_gameObjects)
        i->draw();
}

bool PauseState::onEnter()
{
    ManageTexture::GetInstance()->load("Image/pause.png","pause",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_restart.png","restart",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_options.png","options",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_home.png","home",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_resume.png","resume",Game::GetInstance()->GetRenderer());


    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,270,250,60,"resume"),p_pauseToResume));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,340,250,60,"options"),p_pauseToOptions));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,410,250,60,"restart"),p_pauseToRestart));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,480,250,60,"home"),p_pauseToHome));
    return true;
}

bool PauseState::onExit()
{
    for(GameObject* i:p_gameObjects)
        i->clean();
    p_gameObjects.clear();
    ManageTexture::GetInstance()->clearFromTexMap("instruction");
    HandleInput::GetInstance()->reset();
    return true;
}

