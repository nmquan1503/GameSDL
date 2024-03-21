
#include "ShopState.h"

std::string ShopState::p_ShopID="SHOP";

std::vector<Note*> ShopState::p_notes;
std::vector<GameObject*> ShopState::p_gameObjects;

void ShopState::update()
{
    Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
    Vector2D scr_pos=static_cast<SDLGameObject*>(p_gameObjects[1])->GetPos();
    if(HandleInput::GetInstance()->GetMouse(0))
    {

        if(vec->GetX()>0&&vec->GetX()<60&&vec->GetY()>0&&vec->GetY()<60&&p_scrolling==false)
        {
            Game::GetInstance()->GetGameStateMachine()->popState();
        }

        if((vec->GetX()>scr_pos.GetX()&&vec->GetX()<scr_pos.GetX()+21&&vec->GetY()>115&&vec->GetY()<585)||p_scrolling==true)
        {


            p_scrolling=true;
            int y_new=std::max(115,std::min((int)(vec->GetY()-150),285));
            static_cast<SDLGameObject*>(p_gameObjects[1])->SetPos(Vector2D(992,y_new));
            for(int i=0; i<p_gameObjects.size(); i++)
            {
                if(i!=1)
                    static_cast<MenuButton*>(p_gameObjects[i])->SetVel(Vector2D(0,(-y_new+y_scr)*2));
            }
            y_scr=y_new;
        }
    }
    else

        p_scrolling=false;


    if(p_scrolling==true||(p_scrolling==false&&vec->GetY()>100))
    {

        for(GameObject* i:p_gameObjects)
        {
            i->update();
        }
    }

    for(GameObject* i:p_gameObjects)
        static_cast<MenuButton*>(i)->SetVel(Vector2D(0,0));

    for(int i=0; i<p_notes.size(); i++)
    {
        if(p_notes[i]->GetTime()>=12)
        {
            p_notes[i]->clean();
            p_notes.erase(p_notes.begin()+i);
            i--;
        }
    }

    for(Note* i:p_notes)
        i->update();
}

void ShopState::render()
{
    p_gameObjects[0]->draw();
    ManageTexture::GetInstance()->draw("scroll1",990,113,25,474,Game::GetInstance()->GetRenderer(),true);
    for(int i=1; i<p_gameObjects.size(); i++)
        p_gameObjects[i]->draw();
    ManageTexture::GetInstance()->draw("gold_data",5,245,110,50,Game::GetInstance()->GetRenderer(),true);
    ManageTexture::GetInstance()->draw("gem_data",5,305,110,50,Game::GetInstance()->GetRenderer(),true);
    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(GameData::GetInstance()->GetGold()), {255,255,0,255},55,255,Game::GetInstance()->GetRenderer());
    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(GameData::GetInstance()->GetGem()), {255,255,0,255},55,315,Game::GetInstance()->GetRenderer());


    ManageTexture::GetInstance()->draw("shop2",0,0,1020,105,Game::GetInstance()->GetRenderer(),true);
    ManageTexture::GetInstance()->draw("return",0,0,60,60,Game::GetInstance()->GetRenderer(),true);

    Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
    Vector2D tmp=static_cast<SDLGameObject*>(p_gameObjects[0])->GetPos();
    if(vec->GetX()>=tmp.GetX()+217&&vec->GetX()<=tmp.GetX()+302&&vec->GetY()>=tmp.GetY()+230&&vec->GetY()<=tmp.GetY()+315&&p_scrolling==false)
        ManageFont::GetInstance()->drawInfo("font2","Your HP will be doubled for 10 seconds\nOwned:"+std::to_string(GameData::GetInstance()->GetHpX2())
                                            , {255,255,0,255},
                                            vec->GetX(),vec->GetY(),200,Game::GetInstance()->GetRenderer());
    else if(vec->GetX()>=tmp.GetX()+471&&vec->GetX()<=tmp.GetX()+556&&vec->GetY()>=tmp.GetY()+228&&vec->GetY()<=tmp.GetY()+313&&p_scrolling==false)
        ManageFont::GetInstance()->drawInfo("font2","Your Mana will be doubled for 10 seconds\nOwned:"+std::to_string(GameData::GetInstance()->GetManaX2())
                                            , {255,255,0,255},
                                            vec->GetX(),vec->GetY(),200,Game::GetInstance()->GetRenderer());
    else if(vec->GetX()>=tmp.GetX()+723&&vec->GetX()<=tmp.GetX()+808&&vec->GetY()>=tmp.GetY()+228&&vec->GetY()<=tmp.GetY()+313&&p_scrolling==false)
        ManageFont::GetInstance()->drawInfo("font2","Your Damage will be doubled for 10 seconds\nOwned:"+std::to_string(GameData::GetInstance()->GetDamageSpell())
                                            , {255,255,0,255},
                                            vec->GetX(),vec->GetY(),200,Game::GetInstance()->GetRenderer());
    else if(vec->GetX()>=tmp.GetX()+220&&vec->GetX()<=tmp.GetX()+305&&vec->GetY()>=tmp.GetY()+555&&vec->GetY()<=tmp.GetY()+640&&p_scrolling==false)
        ManageFont::GetInstance()->drawInfo("font2","You will heal 160 HP per second on average\nOwned:"+std::to_string(GameData::GetInstance()->GetHpSpell())
                                            , {255,255,0,255},
                                            vec->GetX(),vec->GetY(),200,Game::GetInstance()->GetRenderer());
    else if(vec->GetX()>=tmp.GetX()+472&&vec->GetX()<=tmp.GetX()+557&&vec->GetY()>=tmp.GetY()+556&&vec->GetY()<=tmp.GetY()+641&&p_scrolling==false)
        ManageFont::GetInstance()->drawInfo("font2","You will heal 32 Mana per second on average\nOwned:"+std::to_string(GameData::GetInstance()->GetManaSpell())
                                            , {255,255,0,255},
                                            vec->GetX(),vec->GetY(),200,Game::GetInstance()->GetRenderer());
    else if(vec->GetX()>=tmp.GetX()+722&&vec->GetX()<=tmp.GetX()+807&&vec->GetY()>=tmp.GetY()+553&&vec->GetY()<=tmp.GetY()+638&&p_scrolling==false)
        ManageFont::GetInstance()->drawInfo("font2","Your speed will be doubled for 10 seconds\nOwned:"+std::to_string(GameData::GetInstance()->GetSpeedSpell())
                                            , {255,255,0,255},
                                            vec->GetX(),vec->GetY(),200,Game::GetInstance()->GetRenderer());

    for(Note* i:p_notes)
        i->draw();

}

bool ShopState::onEnter()
{
    ManageTexture::GetInstance()->load("Image/shop.png","shop",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/item_100gold.png","item_100gold",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/item_2gem.png","item_2gem",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/scroll1.png","scroll1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/scroll2.png","scroll2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/gold_data.png","gold_data",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/gem_data.png","gem_data",Game::GetInstance()->GetRenderer());
    //ManageTexture::GetInstance()->load("Image/return.png","return",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/bogoc2.png","bogoc2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/shop2.png","shop2",Game::GetInstance()->GetRenderer());

    ManageFont::GetInstance()->load("Font/Fz-Futura-Maxi.ttf","font2",20);
    ManageFont::GetInstance()->load("Font/SuperSquadItalic.ttf","font1",25);


    p_gameObjects.push_back(new SDLGameObject(new LoaderParams(0,0,1020,1140,"shop")));
    p_gameObjects.push_back(new SDLGameObject(new LoaderParams(992,115,21,300,"scroll2")));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(187,355,145,45,"item_2gem"),p_buyHpX2));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(437,355,145,45,"item_2gem"),p_buyManaX2));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(687,355,145,45,"item_2gem"),p_buyDamage));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(187,685,145,45,"item_100gold"),p_buyHP));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(437,685,145,45,"item_100gold"),p_buyMANA));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(687,685,145,45,"item_100gold"),p_buySpeed));

    return true;
}

bool ShopState::onExit()
{
    ManageTexture::GetInstance()->clearFromTexMap("shop");
    ManageTexture::GetInstance()->clearFromTexMap("item_100gold");
    ManageTexture::GetInstance()->clearFromTexMap("item_2gem");
    ManageTexture::GetInstance()->clearFromTexMap("scroll1");
    ManageTexture::GetInstance()->clearFromTexMap("scroll2");
    ManageTexture::GetInstance()->clearFromTexMap("gold_data");
    ManageTexture::GetInstance()->clearFromTexMap("gem_data");
    //ManageTexture::GetInstance()->clearFromTexMap("return");
    ManageTexture::GetInstance()->clearFromTexMap("bogoc2");
    ManageTexture::GetInstance()->clearFromTexMap("shop2");

    ManageFont::GetInstance()->clearFromFontMap("font2");
    ManageFont::GetInstance()->clearFromFontMap("font1");


    for(GameObject* i:p_gameObjects)
        i->clean();
    p_gameObjects.clear();

    for(Note* i:p_notes)
        i->clean();
    p_notes.clear();
    return true;
}

void ShopState::p_buyHP()
{
    if(GameData::GetInstance()->GetGold()>=100)
    {
        GameData::GetInstance()->SetGold(-100);
        GameData::GetInstance()->SetHpSpell(1);
        Vector2D tmp=static_cast<SDLGameObject*>(p_gameObjects[5])->GetPos();
        p_notes.push_back(new Note("font1","+1",tmp.GetX()+72,tmp.GetY()-70,150, {255,255,0,255}));
    }
    else p_notes.push_back(new Note("font1","You don't have enough money",510,150,800, {255,0,0,255}));
}

void ShopState::p_buyMANA()
{
    if(GameData::GetInstance()->GetGold()>=100)
    {
        GameData::GetInstance()->SetGold(-100);
        GameData::GetInstance()->SetManaSpell(1);
        Vector2D tmp=static_cast<SDLGameObject*>(p_gameObjects[6])->GetPos();
        p_notes.push_back(new Note("font1","+1",tmp.GetX()+72,tmp.GetY()-70,150, {255,255,0,255}));
    }
    else p_notes.push_back(new Note("font1","You don't have enough money",510,150,800, {255,0,0,255}));
}

void ShopState::p_buyDamage()
{
    if(GameData::GetInstance()->GetGem()>=2)
    {
        GameData::GetInstance()->SetGem(-2);
        GameData::GetInstance()->SetDamageSpell(1);
        Vector2D tmp=static_cast<SDLGameObject*>(p_gameObjects[4])->GetPos();
        p_notes.push_back(new Note("font1","+1",tmp.GetX()+72,tmp.GetY()-70,150, {255,255,0,255}));
    }
    else p_notes.push_back(new Note("font1","You don't have enough money",510,150,800, {255,0,0,255}));
}

void ShopState::p_buyHpX2()
{
    if(GameData::GetInstance()->GetGem()>=2)
    {
        GameData::GetInstance()->SetGem(-2);
        GameData::GetInstance()->SetHpX2(1);
        Vector2D tmp=static_cast<SDLGameObject*>(p_gameObjects[2])->GetPos();
        p_notes.push_back(new Note("font1","+1",tmp.GetX()+72,tmp.GetY()-70,150, {255,255,0,255}));
    }
    else p_notes.push_back(new Note("font1","You don't have enough money",510,150,800, {255,0,0,255}));
}

void ShopState::p_buyManaX2()
{
    if(GameData::GetInstance()->GetGem()>=2)
    {
        GameData::GetInstance()->SetGem(-2);
        GameData::GetInstance()->SetManaX2(1);
        Vector2D tmp=static_cast<SDLGameObject*>(p_gameObjects[3])->GetPos();
        p_notes.push_back(new Note("font1","+1",tmp.GetX()+72,tmp.GetY()-70,150, {255,255,0,255}));
    }
    else p_notes.push_back(new Note("font1","You don't have enough money",510,150,800, {255,0,0,255}));
}

void ShopState::p_buySpeed()
{
    if(GameData::GetInstance()->GetGold()>=100)
    {
        GameData::GetInstance()->SetGold(-100);
        GameData::GetInstance()->SetSpeedSpell(1);
        Vector2D tmp=static_cast<SDLGameObject*>(p_gameObjects[7])->GetPos();
        p_notes.push_back(new Note("font1","+1",tmp.GetX()+72,tmp.GetY()-70,150, {255,255,0,255}));
    }
    else p_notes.push_back(new Note("font1","You don't have enough money",510,150,800, {255,0,0,255}));
}
