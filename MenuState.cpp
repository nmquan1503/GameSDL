

#include "MenuState.h"
#include "MenuBG.h"

std::string MenuState::p_MenuID="MENU";

void MenuState::update()
{
    for(GameObject* i:p_gameObjects)
        i->update();
}

void MenuState::render()
{
    p_gameObjects[0]->draw();
    ManageTexture::GetInstance()->draw("menu",0,0,1020,600,Game::GetInstance()->GetRenderer(),true);
    for(int i=1;i<p_gameObjects.size();i++)
    {
        p_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter()
{
    ManageTexture::GetInstance()->load("Image/backgroud.png","bgmenu",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu.png","menu",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_play.png","play",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_quit.png","quit",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_options.png","options",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_instructions.png","instructions",Game::GetInstance()->GetRenderer());

    p_gameObjects.push_back(new MenuBG(new LoaderParams(0,0,2040,600,"bgmenu")));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,270,250,60,"play"),p_menuToPlay));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,340,250,60,"options"),p_menuToOptions));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,410,250,60,"instructions"),p_menuToInstruction));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,480,250,60,"quit"),p_exitFromMenu));
    return true;
}

bool MenuState::onExit()
{
    for(GameObject* i:p_gameObjects)
    {
        i->clean();
    }
    p_gameObjects.clear();

    ManageTexture::GetInstance()->clearFromTexMap("bgmenu");
    ManageTexture::GetInstance()->clearFromTexMap("play");
    ManageTexture::GetInstance()->clearFromTexMap("menu");
    ManageTexture::GetInstance()->clearFromTexMap("quit");
    ManageTexture::GetInstance()->clearFromTexMap("options");
    ManageTexture::GetInstance()->clearFromTexMap("instructions");
    return true;
}

void MenuState::p_menuToPlay()
{
    Game::GetInstance()->GetGameStateMachine()->changeState(new PlayState());
}

void MenuState::p_exitFromMenu()
{
    Game::GetInstance()->GetGameStateMachine()->changeState(new SureState());
}

void MenuState::p_menuToOptions()
{
    Game::GetInstance()->GetGameStateMachine()->changeState(new OptionsState());
}

void MenuState::p_menuToInstruction()
{
    Game::GetInstance()->GetGameStateMachine()->changeState(new InstructionState());
}
