#include "GameOverState.h"

std::string GameOverState::p_GameOverID="GAMEOVER";

GameOverState:: GameOverState(SDL_Texture* tex):p_tex(tex)
{}

void GameOverState::update()
{
    for(GameObject* i:p_gameObjects)
        i->update();
}

void GameOverState::render()
{
    SDL_RenderCopy(Game::GetInstance()->GetRenderer(),p_tex,NULL,NULL);
    ManageTexture::GetInstance()->draw("gameover",216,220,588,60,Game::GetInstance()->GetRenderer(),true);
    for(GameObject* i:p_gameObjects)
        i->draw();
}

bool GameOverState::onEnter()
{
    //Game::GetInstance()->GetGameStateMachine()->clearAllBefore();
    ManageTexture::GetInstance()->load("Image/gameover.png","gameover",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_restart.png","restart",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_home.png","home",Game::GetInstance()->GetRenderer());

    p_gameObjects.push_back(new MenuButton(new LoaderParams(250,310,250,60,"restart"),p_toRestart));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(520,310,250,60,"home"),p_toHome));

    return true;
}

bool GameOverState::onExit()
{
    for(GameObject* i:p_gameObjects)
        i->clean();
    p_gameObjects.clear();
    ManageTexture::GetInstance()->clearFromTexMap("gameover");
    ManageTexture::GetInstance()->clearFromTexMap("restart");
    ManageTexture::GetInstance()->clearFromTexMap("home");

    return true;
}

void GameOverState::p_toHome()
{
    Game::GetInstance()->GetGameStateMachine()->clearAllState();
    Game::GetInstance()->GetGameStateMachine()->changeState(new MenuState());
}
void GameOverState::p_toRestart()
{
    Game::GetInstance()->GetGameStateMachine()->clearAllState();
    Game::GetInstance()->GetGameStateMachine()->changeState(new PlayState());
}
