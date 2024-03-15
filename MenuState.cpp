

#include "MenuState.h"
#include "MenuBG.h"

std::string MenuState::p_MenuID="MENU";
std::vector<GameObject*> MenuState::p_gameObjects;
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
    ManageTexture::GetInstance()->load("Image/menu_shop.png","shop_menu",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_upgrade.png","menu_upgrade",Game::GetInstance()->GetRenderer());


    ManageSound::GetInstance()->load("Audio/SoundMenu.mp3","soundmenu",SOUND_MUSIC);


    ManageSound::GetInstance()->playMusic("soundmenu",-1);

    p_gameObjects.push_back(new MenuBG(new LoaderParams(0,0,2040,600,"bgmenu"),-5));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,270,250,60,"play"),p_menuToPlay));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,340,250,60,"options"),p_menuToOptions));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,410,250,60,"instructions"),p_menuToInstruction));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,480,250,60,"quit"),p_exitFromMenu));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(770,0,200,130,"shop_menu"),p_menuToShop));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(770,170,200,124,"menu_upgrade"),p_menuToUpgrade));
    return true;
}

bool MenuState::onExit()
{
    for(GameObject* i:p_gameObjects)
    {
        i->clean();
    }
    p_gameObjects.clear();

    ManageSound::GetInstance()->stopMusic();

    ManageTexture::GetInstance()->clearFromTexMap("bgmenu");
    ManageTexture::GetInstance()->clearFromTexMap("play");
    ManageTexture::GetInstance()->clearFromTexMap("menu");
    ManageTexture::GetInstance()->clearFromTexMap("quit");
    ManageTexture::GetInstance()->clearFromTexMap("options");
    ManageTexture::GetInstance()->clearFromTexMap("instructions");
    ManageTexture::GetInstance()->clearFromTexMap("shop_menu");
    ManageTexture::GetInstance()->clearFromTexMap("menu_upgrade");


    ManageSound::GetInstance()->clearFromMusicMap("soundmenu");
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
    GameObject* p_g=(p_gameObjects[0]);
    Game::GetInstance()->GetGameStateMachine()->pushState(new OptionsState(p_g));
}

void MenuState::p_menuToInstruction()
{
    Game::GetInstance()->GetGameStateMachine()->changeState(new InstructionState());
}

void MenuState::p_menuToShop()
{
    Game::GetInstance()->GetGameStateMachine()->pushState(new ShopState());
}

void MenuState::p_menuToUpgrade()
{
    Game::GetInstance()->GetGameStateMachine()->pushState(new PlayerInfo());
}
