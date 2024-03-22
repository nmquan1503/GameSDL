
#include "PauseState.h"

std::string PauseState::p_PauseID="PAUSE";
int PauseState::Map_ID;

PauseState::PauseState(SDL_Texture* tex,int ID):p_tex(tex)
{
    ManageTexture::GetInstance()->loadFromTex(p_tex,"blind",Game::GetInstance()->GetRenderer());
    Map_ID=ID;
}

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
    Game::GetInstance()->GetGameStateMachine()->clearAllState();
    Game::GetInstance()->GetGameStateMachine()->changeState(new MenuState());
}

void PauseState::p_pauseToRestart()
{
    Game::GetInstance()->GetGameStateMachine()->clearAllState();
    if(Map_ID==1)
        Game::GetInstance()->GetGameStateMachine()->changeState(new PlayState());
    else if(Map_ID==3)
        Game::GetInstance()->GetGameStateMachine()->changeState(new PlayState3());
}

void PauseState::p_pauseToOptions()
{
    Game::GetInstance()->GetGameStateMachine()->pushState(new OptionsState(new MenuBG(new LoaderParams(0,0,1020,600,"blind"),0)));
}

void PauseState::update()
{
    for(GameObject* i:p_gameObjects)
        i->update();
}

void PauseState::render()
{
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

    ManageSound::GetInstance()->load("Audio/button.mp3","button",SOUND_SFX);


    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,270,250,60,"resume"),p_pauseToResume));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,340,250,60,"options"),p_pauseToOptions));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,410,250,60,"restart"),p_pauseToRestart));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,480,250,60,"home"),p_pauseToHome));
    return true;
}

bool PauseState::onExit()
{
    SDL_DestroyTexture(p_tex);
    for(GameObject* i:p_gameObjects)
    {
        i->clean();
    }
    p_gameObjects.clear();
    ManageTexture::GetInstance()->clearFromTexMap("instruction");
    ManageTexture::GetInstance()->clearFromTexMap("pause");
    ManageTexture::GetInstance()->clearFromTexMap("restart");
    ManageTexture::GetInstance()->clearFromTexMap("options");
    ManageTexture::GetInstance()->clearFromTexMap("home");
    ManageTexture::GetInstance()->clearFromTexMap("resume");
    ManageTexture::GetInstance()->clearFromTexMap("blind");

    ManageSound::GetInstance()->clearFromSFXMap("button");

    HandleInput::GetInstance()->reset();
    return true;
}

