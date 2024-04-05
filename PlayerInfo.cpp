#include "PlayerInfo.h"
#include "EspFunction.cpp"

std::string PlayerInfo::p_PlInfo="PLAYERINFO";

std::vector<Note*> PlayerInfo::p_notes;
int PlayerInfo::dart_rate;
int PlayerInfo::dmg_rate;
int PlayerInfo::hp_rate;
int PlayerInfo::mana_rate;
bool PlayerInfo::view;
int PlayerInfo::distance_dart;
int PlayerInfo::frame_player;
int PlayerInfo::row_player;
SDL_Texture* PlayerInfo::tex;
std::vector<GameObject*> PlayerInfo::p_gameObjects;
std::vector<GameObject*> PlayerInfo::p_animation;

PlayerInfo::PlayerInfo()
{
    hp_rate=100-5*(GameData::GetInstance()->GetHpPlayer()-1000)/500;
    mana_rate=100-5*(GameData::GetInstance()->GetManaPlayer()-200)/50;
    dmg_rate=100-5*(GameData::GetInstance()->GetDamagePlayer()-40)/20;
    if(GameData::GetInstance()->GetLevelDart()==1)dart_rate=50;
    else dart_rate=20;
    view=false;
    frame_player=0;
    row_player=1;
    distance_dart=0;
    tex=NULL;
}

void PlayerInfo::update()
{


    Vector2D* vec=HandleInput::GetInstance()->GetMousePos();

    if(view==true)
    {
        distance_dart=(++distance_dart)%20;
        if(distance_dart==0)
        {
            row_player=2;
            frame_player=0;
        }
        else
        {
            row_player=1;
            frame_player=(++frame_player)%5;
        }
        p_gameObjects.back()->update();
    }

    else
    {

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
                for(int i=0; i<p_gameObjects.size()-1; i++)
                {
                    if(i!=1)
                        static_cast<MenuButton*>(p_gameObjects[i])->SetVel(Vector2D(0,(-y_new+y_scr)*2));
                }
                for(GameObject* i:p_animation)
                    static_cast<MenuButton*>(i)->SetVel(Vector2D(0,(-y_new+y_scr)*2));
                y_scr=y_new;
            }
        }
        else
            p_scrolling=false;

        if(p_scrolling==true||(p_scrolling==false&&vec->GetY()>100))
        {
            p_gameObjects[0]->update();
            p_gameObjects[1]->update();
            if(GameData::GetInstance()->GetLevelDart()<3)p_gameObjects[2]->update();
            if(GameData::GetInstance()->GetDamagePlayer()<400)p_gameObjects[3]->update();
            if(GameData::GetInstance()->GetHpPlayer()<10000)p_gameObjects[4]->update();
            if(GameData::GetInstance()->GetManaPlayer()<1000)p_gameObjects[5]->update();
            p_gameObjects[6]->update();
        }

        for(int i=0; i<p_gameObjects.size(); i++)
            static_cast<MenuButton*>(p_gameObjects[i])->SetVel(Vector2D(0,0));
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
        for(int i=0; i<p_animation.size(); i++)
        {
            if(static_cast<Animation*>(p_animation[i])->GetTime()>=5)
            {
                p_animation.erase(p_animation.begin()+i);
                i--;
            }
        }
        for(GameObject* i:p_animation)
            i->update();

    }

}

void PlayerInfo::render()
{
    if(view==true)
    {
        SDL_RenderCopy(Game::GetInstance()->GetRenderer(),tex,NULL,NULL);
        if(GameData::GetInstance()->GetHpPlayer()<5000)
            ManageTexture::GetInstance()->drawFrame("player1",300,200,50,75,frame_player,row_player,
                                                    Game::GetInstance()->GetRenderer(),true);
        else ManageTexture::GetInstance()->drawFrame("player2",300,200,50,75,frame_player,row_player,
                    Game::GetInstance()->GetRenderer(),true);

        if(GameData::GetInstance()->GetLevelDart()==1)
            ManageTexture::GetInstance()->drawFrame("dart",360+distance_dart*20,230,25,25,distance_dart%2,
                                                    0,Game::GetInstance()->GetRenderer(),true);
        else if(GameData::GetInstance()->GetLevelDart()==2)
            ManageTexture::GetInstance()->drawFrame("dart_2",360+distance_dart*20,230,25,25,distance_dart%2,
                                                    0,Game::GetInstance()->GetRenderer(),true);
        else ManageTexture::GetInstance()->drawFrame("dart_3",360+distance_dart*20,230,35,35,distance_dart%2,
                    0,Game::GetInstance()->GetRenderer(),true);

        p_gameObjects.back()->draw();
    }
    else
    {

        p_gameObjects[0]->draw();

        Vector2D v=static_cast<SDLGameObject*>(p_gameObjects[0])->GetPos();

        if(GameData::GetInstance()->GetLevelDart()<3)
        {
            int tmp=GameData::GetInstance()->GetLevelDart();
            ManageFont::GetInstance()->drawTextBlended("font2","Level: "+std::to_string(tmp)+" (Damage: "+std::to_string(15*tmp*tmp-15*tmp+10)+")"
                    , {255,255,0,255},
                    335,v.GetY()+180,
                    Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font2","Upgrade:+1(Dmg:+"+std::to_string(30*tmp)+")"
                    , {255,255,0,255},
                    335,v.GetY()+210,
                    Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font2","Rate: "+std::to_string(dart_rate)+"%"
                    , {255,255,0,255},
                    335,v.GetY()+240,
                    Game::GetInstance()->GetRenderer());
        }
        else ManageFont::GetInstance()->drawTextBlended("font2","Level: Max(Damage:100)",
        {255,255,0,255},
        335,v.GetY()+210,
        Game::GetInstance()->GetRenderer());

        if(GameData::GetInstance()->GetDamagePlayer()<400)
        {
            int tmp=GameData::GetInstance()->GetDamagePlayer();
            ManageFont::GetInstance()->drawTextBlended("font2","Damage: "+std::to_string(tmp)
                    , {255,255,0,255},
                    335,v.GetY()+380,
                    Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font2","Upgrade: +20"
                    , {255,255,0,255},
                    335,v.GetY()+410,
                    Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font2","Rate: "+std::to_string(dmg_rate)+"%"
                    , {255,255,0,255},
                    335,v.GetY()+440,
                    Game::GetInstance()->GetRenderer());
        }
        else ManageFont::GetInstance()->drawTextBlended("font2","Level: Max(Damage:400)",
        {255,255,0,255},
        335,v.GetY()+410,
        Game::GetInstance()->GetRenderer());

        if(GameData::GetInstance()->GetHpPlayer()<10000)
        {
            int tmp=GameData::GetInstance()->GetHpPlayer();
            ManageFont::GetInstance()->drawTextBlended("font2","HP: "+std::to_string(tmp)
                    , {255,255,0,255},
                    335,v.GetY()+580,
                    Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font2","Upgrade:+500"
                    , {255,255,0,255},
                    335,v.GetY()+610,
                    Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font2","Rate: "+std::to_string(hp_rate)+"%"
                    , {255,255,0,255},
                    335,v.GetY()+640,
                    Game::GetInstance()->GetRenderer());
        }
        else ManageFont::GetInstance()->drawTextBlended("font2","Level: Max(HP:10000)",
        {255,255,0,255},
        335,v.GetY()+610,
        Game::GetInstance()->GetRenderer());

        if(GameData::GetInstance()->GetManaPlayer()<1000)
        {
            int tmp=GameData::GetInstance()->GetManaPlayer();
            ManageFont::GetInstance()->drawTextBlended("font2","Mana: "+std::to_string(tmp)
                    , {255,255,0,255},
                    335,v.GetY()+780,
                    Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font2","Upgrade:+50"
                    , {255,255,0,255},
                    335,v.GetY()+810,
                    Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font2","Rate: "+std::to_string(mana_rate)+"%"
                    , {255,255,0,255},
                    335,v.GetY()+840,
                    Game::GetInstance()->GetRenderer());
        }
        else ManageFont::GetInstance()->drawTextBlended("font2","Level: Max(Mana:1000)",
        {255,255,0,255},
        335,v.GetY()+810,
        Game::GetInstance()->GetRenderer());

        ManageTexture::GetInstance()->draw("scroll1",990,113,25,474,Game::GetInstance()->GetRenderer(),true);

        p_gameObjects[1]->draw();
        if(GameData::GetInstance()->GetLevelDart()<3)p_gameObjects[2]->draw();
        if(GameData::GetInstance()->GetDamagePlayer()<400)p_gameObjects[3]->draw();
        if(GameData::GetInstance()->GetHpPlayer()<10000)p_gameObjects[4]->draw();
        if(GameData::GetInstance()->GetManaPlayer()<1000)p_gameObjects[5]->draw();

        ManageTexture::GetInstance()->draw("gold_data",770,150,110,50,Game::GetInstance()->GetRenderer(),true);
        ManageTexture::GetInstance()->draw("gem_data",770,210,110,50,Game::GetInstance()->GetRenderer(),true);
        ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(GameData::GetInstance()->GetGold()), {255,255,0,255},820,160,Game::GetInstance()->GetRenderer());
        ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(GameData::GetInstance()->GetGem()), {255,255,0,255},820,220,Game::GetInstance()->GetRenderer());


        for(GameObject* i:p_animation)
            i->draw();

        ManageTexture::GetInstance()->draw("upgrade2",0,0,1020,124,Game::GetInstance()->GetRenderer(),true);
        ManageTexture::GetInstance()->draw("return",0,0,60,60,Game::GetInstance()->GetRenderer(),true);


        for(Note* i:p_notes)
            i->draw();

        p_gameObjects.back()->draw();
    }
}

bool PlayerInfo::onEnter()
{
    ManageTexture::GetInstance()->load("Image/upgrade.png","upgrade",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/item_100gold.png","item_100gold",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/item_2gem.png","item_2gem",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/scroll1.png","scroll1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/scroll2.png","scroll2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/gold_data.png","gold_data",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/gem_data.png","gem_data",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/upgrade2.png","upgrade2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/succeed_upgrade.png","succeed_upgrade",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/player1.png","player1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/player2.png","player2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/dart.png","dart",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/dart_2.png","dart_2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/dart_3.png","dart_3",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/view.png","view",Game::GetInstance()->GetRenderer());


    ManageFont::GetInstance()->load("Font/Fz-Futura-Maxi.ttf","font2",20);
    ManageFont::GetInstance()->load("Font/SuperSquadItalic.ttf","font1",25);

    ManageSound::GetInstance()->load("Audio/succeed_upgrade.mp3","succeed_upgrade",SOUND_SFX);

    p_gameObjects.push_back(new SDLGameObject(new LoaderParams(0,0,1020,1140,"upgrade")));
    p_gameObjects.push_back(new SDLGameObject(new LoaderParams(992,115,21,300,"scroll2")));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(585,202,145,45,"item_2gem"),p_upgradeDart));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(585,402,145,45,"item_2gem"),p_upgradeDmg));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(585,602,145,45,"item_100gold"),p_upgradeHP));
    p_gameObjects.push_back(new MenuButton(new LoaderParams(585,802,145,45,"item_100gold"),p_upgradeMana));

    p_gameObjects.push_back(new MenuButton(new LoaderParams(900,200,80,80,"view"),p_view));


    return true;
}

bool PlayerInfo::onExit()
{

    for(GameObject* i:p_gameObjects)
    {
        i->clean();
    }
    p_gameObjects.clear();

    for(Note* i: p_notes)
    {
        i->clean();
    }
    p_notes.clear();

    for(GameObject* i : p_animation)
        i->clean();
    p_animation.clear();

    if(tex!=NULL)
        SDL_DestroyTexture(tex);


    ManageTexture::GetInstance()->clearFromTexMap("upgrade");
    ManageTexture::GetInstance()->clearFromTexMap("item_100gold");
    ManageTexture::GetInstance()->clearFromTexMap("item_2gem");
    ManageTexture::GetInstance()->clearFromTexMap("scroll1");
    ManageTexture::GetInstance()->clearFromTexMap("scroll2");
    ManageTexture::GetInstance()->clearFromTexMap("gold_data");
    ManageTexture::GetInstance()->clearFromTexMap("gem_data");
    ManageTexture::GetInstance()->clearFromTexMap("upgrade2");
    ManageTexture::GetInstance()->clearFromTexMap("succeed_upgrade");
    ManageTexture::GetInstance()->clearFromTexMap("player1");
    ManageTexture::GetInstance()->clearFromTexMap("player2");
    ManageTexture::GetInstance()->clearFromTexMap("dart");
    ManageTexture::GetInstance()->clearFromTexMap("dart_2");
    ManageTexture::GetInstance()->clearFromTexMap("dart_3");
    ManageTexture::GetInstance()->clearFromTexMap("view");

    ManageFont::GetInstance()->clearFromFontMap("font2");
    ManageFont::GetInstance()->clearFromFontMap("font1");

    ManageSound::GetInstance()->clearFromSFXMap("succeed_upgrade");


    return true;
}

void PlayerInfo::p_upgradeHP()
{
    if(GameData::GetInstance()->GetGold()>=100)
    {
        int t=rand()%100+1;
        if(t<=hp_rate)
        {
            GameData::GetInstance()->SetHpPlayer(500);
            GameData::GetInstance()->SetGold(-100);
            p_notes.push_back(new Note("font1","Upgrade successful!",510,150,800, {255,0,0,255}));
            p_animation.push_back(new Animation(new LoaderParams(212,static_cast<SDLGameObject*>(p_gameObjects[0])->GetPos().GetY()+600,50,50,"succeed_upgrade"),6));
            ManageSound::GetInstance()->playSound("succeed_upgrade",0);
            hp_rate-=5;
        }
        else
        {
            GameData::GetInstance()->SetGold(-100);
            p_notes.push_back(new Note("font1","Failed.",510,150,800, {255,0,0,255}));
        }
    }
    else p_notes.push_back(new Note("font1","You don't have enough money",510,150,800, {255,0,0,255}));
}

void PlayerInfo::p_upgradeMana()
{
    if(GameData::GetInstance()->GetGold()>=100)
    {
        int t=rand()%100+1;
        if(t<=mana_rate)
        {
            GameData::GetInstance()->SetManaPlayer(50);
            GameData::GetInstance()->SetGold(-100);
            p_notes.push_back(new Note("font1","Upgrade successful!",510,150,800, {255,0,0,255}));
            p_animation.push_back(new Animation(new LoaderParams(212,static_cast<SDLGameObject*>(p_gameObjects[0])->GetPos().GetY()+800,50,50,"succeed_upgrade"),6));
            ManageSound::GetInstance()->playSound("succeed_upgrade",0);
            mana_rate-=5;
        }
        else
        {
            GameData::GetInstance()->SetGold(-100);
            p_notes.push_back(new Note("font1","Failed.",510,150,800, {255,0,0,255}));
        }
    }
    else p_notes.push_back(new Note("font1","You don't have enough money",510,150,800, {255,0,0,255}));
}

void PlayerInfo::p_upgradeDmg()
{
    if(GameData::GetInstance()->GetGem()>=2)
    {
        int t=rand()%100+1;
        if(t<=dmg_rate)
        {
            GameData::GetInstance()->SetDamagePlayer(20);
            GameData::GetInstance()->SetGem(-2);
            p_notes.push_back(new Note("font1","Upgrade successful!",510,150,800, {255,0,0,255}));
            p_animation.push_back(new Animation(new LoaderParams(210,static_cast<SDLGameObject*>(p_gameObjects[0])->GetPos().GetY()+400,50,50,"succeed_upgrade"),6));
            ManageSound::GetInstance()->playSound("succeed_upgrade",0);
            dmg_rate-=5;
        }
        else
        {
            GameData::GetInstance()->SetGem(-2);
            p_notes.push_back(new Note("font1","Failed.",510,150,800, {255,0,0,255}));
        }
    }
    else p_notes.push_back(new Note("font1","You don't have enough money",510,150,800, {255,0,0,255}));
}

void PlayerInfo::p_upgradeDart()
{
    if(GameData::GetInstance()->GetGem()>=2)
    {
        int t=rand()%100+1;
        if(t<=dart_rate)
        {
            GameData::GetInstance()->SetLevelDart(1);
            GameData::GetInstance()->SetGem(-2);
            p_notes.push_back(new Note("font1","Upgrade successful!",510,150,800, {255,0,0,255}));
            p_animation.push_back(new Animation(new LoaderParams(210,static_cast<SDLGameObject*>(p_gameObjects[0])->GetPos().GetY()+200,50,50,"succeed_upgrade"),6));
            ManageSound::GetInstance()->playSound("succeed_upgrade",0);
            dart_rate-=30;
        }
        else
        {
            GameData::GetInstance()->SetGem(-2);
            p_notes.push_back(new Note("font1","Failed.",510,150,800, {255,0,0,255}));
        }
    }
    else p_notes.push_back(new Note("font1","You don't have enough money",510,150,800, {255,0,0,255}));
}

void PlayerInfo::p_view()
{
    view =!view;
    SDL_DestroyTexture(tex);
    tex=blindTex(Game::GetInstance()->GetRenderer());
}
