
#include "MenuState.h"

std::string MenuState::p_MenuID="MENU";
std::vector<GameObject*> MenuState::p_gameObjects;
bool MenuState::play;
bool MenuState::quit;
bool MenuState::loading;
int MenuState::map_next;



void MenuState::update()
{
    if(loading==false)
    {
        if(play==true)
        {
            Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
            if(HandleInput::GetInstance()->GetMouse(0)&&vec->GetX()<=60&&vec->GetY()<=60)play=false;
            else
            {
                p_gameObjects[0]->update();
                p_gameObjects[7]->update();
                p_gameObjects[8]->update();
            }
        }
        else if(quit==true)
        {
            p_gameObjects[0]->update();
            p_gameObjects[9]->update();
            p_gameObjects[10]->update();
        }
        else
        {
            for(int i=0; i<=6; i++)
                p_gameObjects[i]->update();
        }
    }
    else
    {
        load->update();
        if(static_cast<Wait*>(load)->GetTime()>3100)
        {
            if(map_next==1)Game::GetInstance()->GetGameStateMachine()->changeState(new PlayState());
            else Game::GetInstance()->GetGameStateMachine()->changeState(new PlayState3());
        }
    }
}

void MenuState::render()
{
    SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(),0,0,0,255);
    if(loading==false)
    {
        p_gameObjects[0]->draw();
        if(play==true)
        {
            p_gameObjects[7]->draw();
            p_gameObjects[8]->draw();
            ManageTexture::GetInstance()->draw("return",0,0,60,60,Game::GetInstance()->GetRenderer(),true);
        }
        else if(quit==true)
        {
            p_gameObjects[9]->draw();
            p_gameObjects[10]->draw();
            ManageTexture::GetInstance()->draw("sure",260,120,500,130,Game::GetInstance()->GetRenderer(),true);
        }
        else
        {

            ManageTexture::GetInstance()->draw("menu",0,0,1020,600,Game::GetInstance()->GetRenderer(),true);
            ManageTexture::GetInstance()->draw("day2",770,0,200,171,Game::GetInstance()->GetRenderer(),true);
            for(int i=1; i<=6; i++)
            {
                p_gameObjects[i]->draw();
            }
        }
    }
    else
    {
        load->draw();
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
    ManageTexture::GetInstance()->load("Image/typeplay1.png","typeplay1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/typeplay2.png","typeplay2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/return.png","return",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/sure.png","sure",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/yes.png","yes",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/no.png","no",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/day2.png","day2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/loading1.png","loading1",Game::GetInstance()->GetRenderer());


    ManageSound::GetInstance()->load("Audio/SoundMenu.mp3","soundmenu",SOUND_MUSIC);
    ManageSound::GetInstance()->load("Audio/button.mp3","button",SOUND_SFX);


    ManageSound::GetInstance()->playMusic("soundmenu",-1);

    p_gameObjects.push_back(new MenuBG(new LoaderParams(0,0,1020,600,"bgmenu"),5,2040));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,270,250,60,"play"),p_menuToPlay));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,340,250,60,"options"),p_menuToOptions));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,410,250,60,"instructions"),p_menuToInstruction));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(385,480,250,60,"quit"),p_exitFromMenu));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(770,35,200,95,"shop_menu"),p_menuToShop));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(770,170,200,124,"menu_upgrade"),p_menuToUpgrade));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(160,200,330,215,"typeplay1"),p_menuToMap1));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(530,200,330,215,"typeplay2"),p_menuToMap3));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(320,270,150,80,"yes"),p_quit));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(580,270,150,80,"no"),p_backMenu));


    quit=false;
    play=false;
    loading=false;
    load=new Wait(new LoaderParams(255,260,500,70,"loading1"),2);


    return true;
}

bool MenuState::onExit()
{
    for(GameObject* i:p_gameObjects)
    {
        i->clean();
    }
    p_gameObjects.clear();

    load->clean();

    ManageSound::GetInstance()->stopMusic();

    ManageTexture::GetInstance()->clearFromTexMap("bgmenu");
    ManageTexture::GetInstance()->clearFromTexMap("play");
    ManageTexture::GetInstance()->clearFromTexMap("menu");
    ManageTexture::GetInstance()->clearFromTexMap("quit");
    ManageTexture::GetInstance()->clearFromTexMap("options");
    ManageTexture::GetInstance()->clearFromTexMap("instructions");
    ManageTexture::GetInstance()->clearFromTexMap("shop_menu");
    ManageTexture::GetInstance()->clearFromTexMap("menu_upgrade");
    ManageTexture::GetInstance()->clearFromTexMap("typeplay1");
    ManageTexture::GetInstance()->clearFromTexMap("typeplay2");
    ManageTexture::GetInstance()->clearFromTexMap("return");
    ManageTexture::GetInstance()->clearFromTexMap("sure");
    ManageTexture::GetInstance()->clearFromTexMap("yes");
    ManageTexture::GetInstance()->clearFromTexMap("no");
    ManageTexture::GetInstance()->clearFromTexMap("day2");
    ManageTexture::GetInstance()->clearFromTexMap("loading1");


    ManageSound::GetInstance()->clearFromMusicMap("soundmenu");
    ManageSound::GetInstance()->clearFromSFXMap("button");
    return true;
}

void MenuState::p_menuToPlay()
{
    play=true;
}

void MenuState::p_exitFromMenu()
{
    quit=true;
}

void MenuState::p_menuToOptions()
{
    GameObject* p_g=(p_gameObjects[0]);
    Game::GetInstance()->GetGameStateMachine()->pushState(new OptionsState(p_g));
}

void MenuState::p_menuToInstruction()
{
    Game::GetInstance()->GetGameStateMachine()->pushState(new InstructionState());
}

void MenuState::p_menuToShop()
{
    Game::GetInstance()->GetGameStateMachine()->pushState(new ShopState());
}

void MenuState::p_menuToUpgrade()
{
    Game::GetInstance()->GetGameStateMachine()->pushState(new PlayerInfo());
}

void MenuState::p_menuToMap1()
{
    loading=true;
    map_next=1;
}

void MenuState::p_menuToMap3()
{
    loading=true;
    map_next=3;
}

void MenuState::p_quit()
{
    Game::GetInstance()->quit();
}

void MenuState::p_backMenu()
{
    quit=false;
}
