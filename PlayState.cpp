
#include "PlayState.h"
#include "EspFunction.cpp"


std::string PlayState::p_PlayID="PLAY";

int PlayState::CollisionPlayer(GameObject* g)
{
    int x1=static_cast<Player*>(p_player)->GetPosInMapX(),y1=static_cast<Player*>(p_player)->GetPosInMapY();
    int x2=static_cast<Grass*>(g)->GetFirX(),y2=static_cast<Grass*>(g)->GetFirY(),w2=static_cast<Grass*>(g)->GetW(),h2=static_cast<Grass*>(g)->GetH();
    if(y1+75>y2&&y1<y2+h2&&x1<x2+w2&&x1+50>x2)return 1;
    if(x1<x2+w2&&x1+50>x2+w2)return 2;
    if(x1+50>x2&&x1<x2)return 3;
    return 0;
}

/*bool Collission(GameObject* p1,GameObject* p2)
{
    int x1=static_cast<SDLGameObject*>(p1)->GetPos().GetX(),y1=static_cast<SDLGameObject*>(p1)->GetPos().GetY(),w1=static_cast<SDLGameObject*>(p1)->GetW(),h1=static_cast<SDLGameObject*>(p1)->GetH();
    int x2=static_cast<SDLGameObject*>(p2)->GetPos().GetX(),y2=static_cast<SDLGameObject*>(p2)->GetPos().GetY(),w2=static_cast<SDLGameObject*>(p2)->GetW(),h2=static_cast<SDLGameObject*>(p2)->GetH();
    if(x1>=x2+w2||x1+w1<=x2||y1+h1<=y2||y2+h2<=y1)return false;
    return true;
}*/

/*int Pos(int x,int y)
{
    if(x>400&&x<900&&y+75<=550)return 12;
    if(x>300&&x<550&&y+75<=650)return 11;
    if(x>300&&x<550&&y+75<=750)return 10;
    if(x>950&&x<1335&&y+75<=700)return 5;
    if(x>1430&&x<1680&&y+75<=750)return 13;
    if(x>1740&&y+75<=850)return 14;
    if(x>1285&&x<1395&&y+75<=870)return 8;
    if(x>1345&&x<1455&&y+75<=930)return 9;
    if(x>1405&&x<1515&&y+75<=990)return 15;
    if(x>400&&x<650&&y+75<=850)return 7;
    if(x>700&&x<1000&&y+75<=950)return 4;
    if(x>600&&x<750&&y+75<=1050)return 3;
    if(x<500&&y+75<=1050)return 1;
    if(x>1465&&y+75<=1050)return 6;
    return 2;
}*/

void PlayState::update()
{
    if(static_cast<Player*>(p_player)->GetTimeDie()==20)
    {
        Game::GetInstance()->GetGameStateMachine()->pushState(new GameOverState(blindTex(Game::GetInstance()->GetRenderer()),"gameover",588,60));
    }


    Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
    int x_pl=static_cast<Player*>(p_player)->GetPosInMapX();
    int y_pl=static_cast<Player*>(p_player)->GetPosInMapY();
    int speed_pl=static_cast<Player*>(p_player)->GetSpeed();


    if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE)||(HandleInput::GetInstance()->GetMouse(0)&&vec->GetX()>955&&vec->GetX()<1015&&vec->GetY()>10&&vec->GetY()<70))
    {

        Game::GetInstance()->GetGameStateMachine()->pushState(new PauseState(blindTex(Game::GetInstance()->GetRenderer())));
    }


    if(x_pl>=500&&x_pl<650&&y_pl>=1055)
    {
        static_cast<Player*>(p_player)->SetHP(-1);
        static_cast<Player*>(p_player)->push_hp_lose(-1);
    }

    if(numSoldier==20 && p_soldiers.size()==0)
    {
        p_grass_3.push_back(new Grass(new LoaderParams(1950,1000,50,20,"entrance"),1));
        win=true;
        numSoldier++;
    }

    if(win==true && x_pl>=1940&&y_pl>=850)
    {
        static_cast<Player*>(p_player)->SetPosInMapX(0);
        static_cast<Player*>(p_player)->SetPosInMapY(975);
        Game::GetInstance()->GetGameStateMachine()->pushState(new PlayState2(p_player));
    }




    static_cast<Player*>(p_player)->SetDart(p_darts);


    int t_l=speed_pl,t_r=speed_pl;

    for(GameObject* i:p_grass_1)
    {
        int x2=static_cast<Grass*>(i)->GetFirX(),w2=static_cast<Grass*>(i)->GetW();
        int y2=static_cast<Grass*>(i)->GetFirY(),h2=static_cast<Grass*>(i)->GetH();
        if(y_pl<y2+h2&&y_pl+75>y2)
        {
            if(x_pl-(x2+w2)>=0)t_l=std::min(t_l,x_pl-(x2+w2));
            if(x2-(x_pl+50)>=0)t_r=std::min(t_r,x2-(x_pl+50));
        }
    }
    static_cast<Player*>(p_player)->SetRightCan(t_r);
    static_cast<Player*>(p_player)->SetLeftCan(t_l);

    int t_d=std::min(100,10*static_cast<Player*>(p_player)->GetTimeJump());
    for(GameObject* i:p_grass_1)
    {
        int x2=static_cast<Grass*>(i)->GetFirX(),w2=static_cast<Grass*>(i)->GetW();
        int y2=static_cast<Grass*>(i)->GetFirY();//h2=static_cast<Grass*>(i)->GetH();
        if(x_pl<x2+w2&&x_pl+50>x2)
        {
            if(y2-(y_pl+75)>=0)t_d=std::min(t_d,y2-(y_pl+75));
        }
    }
    for(GameObject* i:p_grass_2)
    {
        int x2=static_cast<Grass*>(i)->GetFirX(),w2=static_cast<Grass*>(i)->GetW();
        int y2=static_cast<Grass*>(i)->GetFirY();//h2=static_cast<Grass*>(i)->GetH();
        if(x_pl<x2+w2&&x_pl+50>x2)
        {
            if(y2-(y_pl+75)>=0)t_d=std::min(t_d,y2-(y_pl+75));
        }
    }
    static_cast<Player*>(p_player)->SetDownCan(t_d);

    p_player->update();



    x_pl=static_cast<Player*>(p_player)->GetPosInMapX();
    y_pl=static_cast<Player*>(p_player)->GetPosInMapY();


    for(GameObject* i: p_grass_1)
    {
        if(CollisionPlayer(i)==1)
        {
            int t=static_cast<Grass*>(i)->GetFirY();
            static_cast<Player*>(p_player)->fixDown(t);
            static_cast<Player*>(p_player)->SetJumped(false);
            static_cast<Player*>(p_player)->SetTimeJump(0);
            break;
        }
    }

    p_darts=static_cast<Player*>(p_player)->GetDarts();
    p_eskill=static_cast<Player*>(p_player)->GetEskill();

    for(GameObject* i:p_darts)
    {
        i->update();
    }

    for(GameObject* i:p_eskill)
        i->update();


    for(int i=0; i<p_animation.size(); i++)
    {
        if(static_cast<Animation*>(p_animation[i])->GetTime()>=4)
        {
            p_animation.erase(p_animation.begin()+i);
            i--;
        }
    }
    for(GameObject* i:p_animation)
        i->update();
    /* int t=Pos(static_cast<Player*>(p_player)->GetPosInMapX(),static_cast<Player*>(p_player)->GetPosInMapX());
     for(GameObject* i:p_soldiers)
     {
         static_cast<Soldier*>(i)->SetPlayerPos(t);
     }*/


    if(numSoldier<20&&p_soldiers.size()<20)
    {
        numSoldier++;
        int k=rand()%2040+1;
        p_soldiers.push_back(new Soldier(new LoaderParams(k,0,60,75,"fide1"),x_pl,y_pl));
    }
    int t=Pos_Map_1(x_pl,y_pl,50,75);

    for(GameObject* i:p_soldiers)
    {
        static_cast<Soldier*>(i)->SetPlayerPos(Pos_Map[ {static_cast<Soldier*>(i)->GetPosMap(),t}]);
        static_cast<Soldier*>(i)->SetMapX(x_pl);
        static_cast<Soldier*>(i)->SetMapY(y_pl);
        i->update();
    }

    for(GameObject* i:p_soldiers)
    {
        if(Collission(i,p_player))
        {
            int t=rand()%2+2;
            static_cast<Player*>(p_player)->SetHP(-t);
            static_cast<Player*>(p_player)->push_hp_lose(-t);
        }
    }

    for(int i=0; i<p_soldiers.size(); i++)
    {
        if(static_cast<Soldier*>(p_soldiers[i])->GetHP()<=0)
        {
            Vector2D tmp=static_cast<SDLGameObject*>(p_soldiers[i])->GetPos();
            p_animation.push_back(new Animation(new LoaderParams(tmp.GetX()-5,tmp.GetY()+10,60,60,"smoke"),4));
            int t=rand()%100+1;
            if(t==1)p_item.push_back(new Item(new LoaderParams(static_cast<Soldier*>(p_soldiers[i])->GetPosInMapX(),static_cast<Soldier*>(p_soldiers[i])->GetPosInMapY(),35,44,"gem"),x_pl,y_pl,"gem"));
            else if(t>=2&&t<=100)p_item.push_back(new Item(new LoaderParams(static_cast<Soldier*>(p_soldiers[i])->GetPosInMapX(),static_cast<Soldier*>(p_soldiers[i])->GetPosInMapY(),35,38,"gold"),x_pl,y_pl,"gold"));
            p_soldiers.erase(p_soldiers.begin()+i);
            i--;
        }
    }




    int dmg_pl=static_cast<Player*>(p_player)->GetDamage();

    for(int i=0; i<p_darts.size(); i++)
    {
        for(int j=0; j<p_soldiers.size(); j++)
        {
            if(Collission(p_darts[i],p_soldiers[j])==true && static_cast<Soldier*>(p_soldiers[j])->GetHP()>0)
            {
                if(GameData::GetInstance()->GetLevelDart()==3)
                {
                    Vector2D tmp=static_cast<SDLGameObject*>(p_soldiers[j])->GetPos();
                    p_animation.push_back(new Animation(new LoaderParams(tmp.GetX(),tmp.GetY()+15,50,50,"big_bang"),4));
                    ManageSound::GetInstance()->playSound("dart3",0);
                }
                else ManageSound::GetInstance()->playSound("atk2",0);
                p_darts.erase(p_darts.begin()+i);
                i--;
                int t=rand()%10+95;
                static_cast<Soldier*>(p_soldiers[j])->SetHP(-(dmg_pl)*t/100);
                static_cast<Soldier*>(p_soldiers[j])->push_hp_lose(-(dmg_pl)*t/100);
                break;
            }
        }
    }


    for(int i=0; i<p_eskill.size(); i++)
    {
        for(int j=0; j<p_soldiers.size(); j++)
        {

            if(Collission(p_eskill[i],p_soldiers[j])&& static_cast<Soldier*>(p_soldiers[j])->GetHP()>0)
            {
                int t=rand()%20+90;
                static_cast<Soldier*>(p_soldiers[j])->SetHP(-dmg_pl*t/10);
                static_cast<Soldier*>(p_soldiers[j])->push_hp_lose(-dmg_pl*t/10);
                break;
            }
        }
    }
    /*for(int i=0; i<p_eskill.size(); i++)
    {
        if(static_cast<Eskill*>(p_eskill[i])->GetTime()>=8)
        {
            p_eskill.erase(p_eskill.begin()+i);
            i--;
        }
    }*/


    for(int i=0; i<p_item.size(); i++)
    {
        if(Collission(p_player,p_item[i]))
        {
            if(static_cast<Item*>(p_item[i])->GetID()=="gold")
                static_cast<Player*>(p_player)->SetGold(1);
            else if(static_cast<Item*>(p_item[i])->GetID()=="gem")
                static_cast<Player*>(p_player)->SetGem(1);

            p_item.erase(p_item.begin()+i);
            i--;
        }
    }


    for(GameObject* i: p_grass_1)
    {
        static_cast<Grass*>(i)->SetMap_X(x_pl);
        static_cast<Grass*>(i)->SetMap_Y(y_pl);
        i->update();
    }
    for(GameObject* i: p_grass_2)
    {
        static_cast<Grass*>(i)->SetMap_X(x_pl);
        static_cast<Grass*>(i)->SetMap_Y(y_pl);
        i->update();
    }
    for(GameObject* i: p_grass_3)
    {
        static_cast<Grass*>(i)->SetMap_X(x_pl);
        static_cast<Grass*>(i)->SetMap_Y(y_pl);
        i->update();
    }
    for(GameObject* i:p_item)
    {
        static_cast<Item*>(i)->SetMap_X(x_pl);
        static_cast<Item*>(i)->SetMap_Y(y_pl);
        i->update();
    }


}

void PlayState::render()
{
    ManageTexture::GetInstance()->draw("backg",0,0,1020,600,Game::GetInstance()->GetRenderer(),true);

    for(GameObject* i:p_grass_1)
        i->draw();

    for(GameObject* i:p_grass_2)
        i->draw();

    for(GameObject* i:p_grass_3)
        i->draw();

    for(GameObject* i:p_soldiers)
    {
        i->draw();
    }
    p_player->draw();
    for(GameObject* i:p_darts)
        i->draw();

    for(GameObject* i:p_eskill)
        i->draw();

    for(GameObject* i:p_item)
        i->draw();

    for(GameObject* i:p_animation)
        i->draw();

    ManageTexture::GetInstance()->draw("pause1",955,10,60,65,Game::GetInstance()->GetRenderer(),true);
    if(win==true)
    {
        ManageFont::GetInstance()->drawTextBlended("font1","Find the entrance", {255,0,0,255},400,100,Game::GetInstance()->GetRenderer());
    }
}


bool PlayState::onEnter()
{
    std::vector<std::vector<int>> v = {{}, {2}, {1, 3}, {2, 4}, {3, 7}, {4, 8}, {15}, {4, 10, 1, 3}, {13, 9}, {8, 15}, {7, 11, 1}, {12, 7, 1}, {5, 11}, {8, 14, 5}, {13, 6}, {9, 6}};
    for(int i=1; i<=15; i++)
    {
        bfs_map(v,i,Pos_Map);
    }
    for(int i=1; i<=15; i++)Pos_Map[ {i,i}]=i;


    ManageTexture::GetInstance()->load("Image/backg.png","backg",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/run.png","run",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/die.png","die",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/nor.png","nor",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/jumpup.png","jumpup",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/jumpdown.png","jumpdown",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/santo.png","santo",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/atk.png","atk",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/dart.png","dart",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/dart_2.png","dart_2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/dart_3.png","dart_3",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/eskill.png","eskill",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/eskill2.png","eskil2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/grass1.png","grass1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/grass2.png","grass2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/grass3.png","grass3",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/grass4.png","grass4",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/grass5.png","grass5",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/grass6.png","grass6",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/bridge1.png","bridge1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/bridge2.png","bridge2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/bridge3.png","bridge3",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/bridge4.png","bridge4",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/bridge.png","bridge",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/kim.png","kim",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/brick1.png","brick1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/brick2.png","brick2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/mai1.png","mai1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/brick3.png","brick3",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/water1.png","water1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/water2.png","water2",Game::GetInstance()->GetRenderer());
    //ManageTexture::GetInstance()->load("Image/tre1.png","tre1",Game::GetInstance()->GetRenderer());
    //ManageTexture::GetInstance()->load("Image/tre2.png","tre2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/mai.png","mai",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/kim1.png","kim1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/day.png","day",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/fide1.png","fide1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/fide3.png","fide3",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/fide4.png","fide4",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/fide5.png","fide5",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/fide6.png","fide6",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/hp1.png","hp1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/hp2.png","hp2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/mana1.png","mana1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/mana2.png","mana2",Game::GetInstance()->GetRenderer());

    //ManageTexture::GetInstance()->load("Image/fire_right.png","fire_right",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/big_bang.png","big_bang",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/smoke.png","smoke",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/gameover.png","gameover",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/pause_1.png","pause1",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/entrance.png","entrance",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/gold.png","gold",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/gem.png","gem",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/gold_data.png","gold_data",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/gem_data.png","gem_data",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/hp_spell.png","hp_spell",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/mana_spell.png","mana_spell",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/damage_spell.png","damage_spell",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/speed_spell.png","speed_spell",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/hp_x2.png","hp_x2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/mana_x2.png","mana_x2",Game::GetInstance()->GetRenderer());



    ManageFont::GetInstance()->load("Font/SuperSquadItalic.ttf","font1",25);
    ManageFont::GetInstance()->load("Font/Fz-Futura-Maxi.ttf","font2",20);
    ManageFont::GetInstance()->load("Font/Lora-Bold.ttf","font3",20);

    ManageSound::GetInstance()->load("Audio/atk1.mp3","atk1",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/atk2.mp3","atk2",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/eskill1.mp3","eskill1",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/dart3.mp3","dart3",SOUND_SFX);



    p_grass_1.push_back(new Grass(new LoaderParams(0,1050,500,150,"grass1"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(500,1160,150,40,"kim"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(650,1050,100,150,"grass5"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(750,950,250,250,"grass6"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1000,700,95,500,"grass4"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1240,1050,800,150,"grass2"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1240,700,95,350,"grass3"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1095,700,145,20,"bridge"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1395,930,60,120,"brick1"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1455,990,60,60,"brick2"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1335,870,60,180,"brick3"),0));

    p_grass_2.push_back(new Grass(new LoaderParams(450,850,200,55,"bridge2"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(350,750,200,55,"bridge2"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(350,650,200,55,"bridge2"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(450,550,450,60,"bridge3"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1480,750,200,20,"bridge4"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1790,850,250,20,"mai1"),0));

    p_grass_3.push_back(new Grass(new LoaderParams(1095,780,145,420,"water1"),1));
    p_grass_3.push_back(new Grass(new LoaderParams(1095,1170,945,30,"water2"),1));
    p_grass_3.push_back(new Grass(new LoaderParams(1790,800,250,250,"mai"),0));
    p_grass_3.push_back(new Grass(new LoaderParams(500,1130,150,30,"kim1"),0));
    p_grass_3.push_back(new Grass(new LoaderParams(1480,0,20,750,"day"),0));
    p_grass_3.push_back(new Grass(new LoaderParams(1660,0,20,750,"day"),0));
    //p_grass_3.push_back(new Grass(new LoaderParams(0,1000,50,20,"entrance"),1));


    //p_gameObjects.push_back(new Soldier(new LoaderParams(900,500,40,65,"soldier1")));
    p_player=new Player(new LoaderParams(0,0,50,75,"nor"));

    return true;
}

bool PlayState::onExit()
{

    for(GameObject* i:p_soldiers)
    {
        i->clean();
    }
    p_soldiers.clear();

    for(GameObject* i:p_grass_1)
    {
        i->clean();
    }
    p_grass_1.clear();

    for(GameObject* i:p_grass_2)
    {
        i->clean();
    }
    p_grass_2.clear();

    for(GameObject* i:p_grass_3)
    {
        i->clean();
    }
    p_grass_3.clear();

    for(GameObject* i:p_darts)
    {
        i->clean();
    }
    p_darts.clear();
    for(GameObject* i:p_eskill)
    {
        i->clean();
    }
    p_eskill.clear();
    p_player->clean();
    for(GameObject* i:p_item)
        i->clean();
    p_item.clear();

    for(GameObject* i:p_animation)
        i->clean();
    p_animation.clear();

    ManageTexture::GetInstance()->clearFromTexMap("backg");
    ManageTexture::GetInstance()->clearFromTexMap("run");
    ManageTexture::GetInstance()->clearFromTexMap("nor");
    ManageTexture::GetInstance()->clearFromTexMap("jumpdown");
    ManageTexture::GetInstance()->clearFromTexMap("jumpup");
    ManageTexture::GetInstance()->clearFromTexMap("santo");
    ManageTexture::GetInstance()->clearFromTexMap("atk");
    ManageTexture::GetInstance()->clearFromTexMap("dart");
    ManageTexture::GetInstance()->clearFromTexMap("dart_2");
    ManageTexture::GetInstance()->clearFromTexMap("dart_3");
    ManageTexture::GetInstance()->clearFromTexMap("eskill");
    ManageTexture::GetInstance()->clearFromTexMap("grass1");
    ManageTexture::GetInstance()->clearFromTexMap("grass2");
    ManageTexture::GetInstance()->clearFromTexMap("grass3");
    ManageTexture::GetInstance()->clearFromTexMap("grass4");
    ManageTexture::GetInstance()->clearFromTexMap("grass5");
    ManageTexture::GetInstance()->clearFromTexMap("grass6");
    ManageTexture::GetInstance()->clearFromTexMap("bridge");
    ManageTexture::GetInstance()->clearFromTexMap("bridge1");
    ManageTexture::GetInstance()->clearFromTexMap("bridge2");
    ManageTexture::GetInstance()->clearFromTexMap("bridge3");
    ManageTexture::GetInstance()->clearFromTexMap("bridge4");
    ManageTexture::GetInstance()->clearFromTexMap("brick1");
    ManageTexture::GetInstance()->clearFromTexMap("brick2");
    ManageTexture::GetInstance()->clearFromTexMap("brick3");
    ManageTexture::GetInstance()->clearFromTexMap("kim");
    ManageTexture::GetInstance()->clearFromTexMap("mai1");
    ManageTexture::GetInstance()->clearFromTexMap("mai");
    ManageTexture::GetInstance()->clearFromTexMap("water1");
    ManageTexture::GetInstance()->clearFromTexMap("water2");
    ManageTexture::GetInstance()->clearFromTexMap("kim1");
    ManageTexture::GetInstance()->clearFromTexMap("day");
    ManageTexture::GetInstance()->clearFromTexMap("fide1");
    ManageTexture::GetInstance()->clearFromTexMap("fide3");
    ManageTexture::GetInstance()->clearFromTexMap("fide4");
    ManageTexture::GetInstance()->clearFromTexMap("fide5");
    ManageTexture::GetInstance()->clearFromTexMap("fide6");
    ManageTexture::GetInstance()->clearFromTexMap("hp1");
    ManageTexture::GetInstance()->clearFromTexMap("hp2");
    ManageTexture::GetInstance()->clearFromTexMap("mana1");
    ManageTexture::GetInstance()->clearFromTexMap("mana2");
    ManageTexture::GetInstance()->clearFromTexMap("gameover");
    ManageTexture::GetInstance()->clearFromTexMap("entrance");
    ManageTexture::GetInstance()->clearFromTexMap("eskill2");
    ManageTexture::GetInstance()->clearFromTexMap("die");
    ManageTexture::GetInstance()->clearFromTexMap("gold");
    ManageTexture::GetInstance()->clearFromTexMap("gem");
    ManageTexture::GetInstance()->clearFromTexMap("gold_data");
    ManageTexture::GetInstance()->clearFromTexMap("gem_data");
    ManageTexture::GetInstance()->clearFromTexMap("hp_spell");
    ManageTexture::GetInstance()->clearFromTexMap("mana_spell");
    ManageTexture::GetInstance()->clearFromTexMap("damage_spell");
    ManageTexture::GetInstance()->clearFromTexMap("pause1");
    ManageTexture::GetInstance()->clearFromTexMap("mana_x2");
    ManageTexture::GetInstance()->clearFromTexMap("hp_x2");
    ManageTexture::GetInstance()->clearFromTexMap("speed_spell");
    ManageTexture::GetInstance()->clearFromTexMap("big_bang");
    ManageTexture::GetInstance()->clearFromTexMap("smoke");




    ManageFont::GetInstance()->clearFromFontMap("font1");
    ManageFont::GetInstance()->clearFromFontMap("font2");
    ManageFont::GetInstance()->clearFromFontMap("font3");



    ManageSound::GetInstance()->clearFromSFXMap("atk1");
    ManageSound::GetInstance()->clearFromSFXMap("atk2");
    ManageSound::GetInstance()->clearFromSFXMap("eskill1");
    ManageSound::GetInstance()->clearFromSFXMap("dart3");

    //ManageSound::GetInstance()->

    return true;
}
