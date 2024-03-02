
#include "SureState.h"

std::string SureState::p_SureID="SURE";

void SureState::update()
{
    for(GameObject* i:p_gameObjects)
        i->update();
}

void SureState::render()
{
     p_gameObjects[0]->draw();
    ManageTexture::GetInstance()->draw("sure",260,120,500,130,Game::GetInstance()->GetRenderer(),true);
    for(int i=1;i<p_gameObjects.size();i++)
    {
        p_gameObjects[i]->draw();
    }
}

bool SureState::onEnter()
{
    ManageTexture::GetInstance()->load("Image/backgroud.png","bgmenu",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/sure.png","sure",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/yes.png","yes",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/no.png","no",Game::GetInstance()->GetRenderer());

    p_gameObjects.push_back(new MenuBG(new LoaderParams(0,0,2040,600,"bgmenu")));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(320,270,150,80,"yes"),p_exit));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(580,270,150,80,"no"),p_backMenu));
    return true;
}

bool SureState::onExit()
{
    for(GameObject* i:p_gameObjects)
    {
        i->clean();
    }
    p_gameObjects.clear();
    //ManageTexture::GetInstance()->clearFromTexMap("bgmenu");
    return true;
}

void SureState::p_backMenu()
{
    Game::GetInstance()->GetGameStateMachine()->changeState(new MenuState());
}

void SureState::p_exit()
{
    Game::GetInstance()->quit();
}
