#include "GameOverState.h"

std::string GameOverState::p_GameOverID="GAMEOVER";

GameOverState:: GameOverState(SDL_Texture* tex,std::string texID,int w,int h):p_tex(tex),p_TexID(texID),p_w(w),p_h(h)
{}

void GameOverState::update()
{
    for(GameObject* i:p_gameObjects)
        i->update();
}

void GameOverState::render()
{
    SDL_RenderCopy(Game::GetInstance()->GetRenderer(),p_tex,NULL,NULL);
    ManageTexture::GetInstance()->draw(p_TexID,(1020-p_w)/2,(600-p_h)/2-80,p_w,p_h,Game::GetInstance()->GetRenderer(),true);
    for(GameObject* i:p_gameObjects)
        i->draw();
}

bool GameOverState::onEnter()
{
    //Game::GetInstance()->GetGameStateMachine()->clearAllBefore();
   //ManageTexture::GetInstance()->load("Image/gameover.png","gameover",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_restart.png","restart",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_home.png","home",Game::GetInstance()->GetRenderer());

    p_gameObjects.push_back(new MenuButton(new LoaderParams(250,(600-p_h)/2-80+p_h+20,250,60,"restart"),p_toRestart));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(520,(600-p_h)/2-80+p_h+20,250,60,"home"),p_toHome));

    return true;
}

bool GameOverState::onExit()
{
    for(GameObject* i:p_gameObjects)
        i->clean();
    p_gameObjects.clear();
    ManageTexture::GetInstance()->clearFromTexMap(p_TexID);
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
