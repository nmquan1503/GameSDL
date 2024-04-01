
#include "PauseState.h"

std::string PauseState::p_PauseID="PAUSE";
int PauseState::Map_ID;
int PauseState::p_gold;
int PauseState::p_gem;
int PauseState::p_time;
int PauseState::p_score;
int PauseState::p_hp_spell;
int PauseState::p_mana_spell;
int PauseState::p_speed_spell;
int PauseState::p_dmg_spell;
int PauseState::p_hp_x2;
int PauseState::p_mana_x2;
SDL_Texture* PauseState::p_tex;

PauseState::PauseState(SDL_Texture* tex,int ID,int gold,int gem,int time,int score,
                       int hp_spell,int mana_spell,int speed_spell,
                       int dmg_spell,int hp_x2,int mana_x2)
{
    ManageTexture::GetInstance()->loadFromTex(p_tex,"blind",Game::GetInstance()->GetRenderer());
    Map_ID=ID;
    p_gold=gold;
    p_gem=gem;
    p_time=time;
    p_score=score;
    p_hp_spell=hp_spell;
    p_mana_spell=mana_spell;
    p_speed_spell=speed_spell;
    p_dmg_spell=dmg_spell;
    p_hp_x2=hp_x2;
    p_mana_x2=mana_x2;
    p_tex=tex;
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
    GameData::GetInstance()->SetGold(p_gold);
    GameData::GetInstance()->SetGem(p_gem);
    GameData::GetInstance()->SetHpSpell(p_hp_spell);
    GameData::GetInstance()->SetManaSpell(p_mana_spell);
    GameData::GetInstance()->SetSpeedSpell(p_speed_spell);
    GameData::GetInstance()->SetDamageSpell(p_dmg_spell);
    GameData::GetInstance()->SetHpX2(p_hp_x2);
    GameData::GetInstance()->SetManaX2(p_mana_x2);

    //Game::GetInstance()->GetGameStateMachine()->clearAllState();

    if(Map_ID==3)
    {

        if(GameData::GetInstance()->GetBestScore()>p_score||(GameData::GetInstance()->GetBestScore()==p_score&&GameData::GetInstance()->GetBestTime()<p_time))
            Game::GetInstance()->GetGameStateMachine()->pushState(new GameOverState(p_tex,"gameover",588,60,p_gold,p_gem,p_score,p_time,3,HOME));
        else Game::GetInstance()->GetGameStateMachine()->pushState(new GameOverState(p_tex,"best_achievement",600,200,p_gold,p_gem,p_score,p_time,3,HOME));
    }
    else if(Map_ID==1)
    {
        Game::GetInstance()->GetGameStateMachine()->pushState(new GameOverState(p_tex,"gameover",588,60,p_gold,p_gem,p_score,p_time,1,HOME));
    }

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

