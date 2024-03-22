#include "PlayState_3.h"
#include "EspFunction.cpp"

std::string PlayState3::p_Play3ID="PLAY3";

void PlayState3::update()
{
    if(static_cast<Player*>(p_player)->GetTimeDie()>=20)
    {
        runTime=false;

        GameData::GetInstance()->SetGold(static_cast<Player*>(p_player)->GetGold());
        GameData::GetInstance()->SetGem(static_cast<Player*>(p_player)->GetGem());
        GameData::GetInstance()->SetHpSpell(static_cast<Player*>(p_player)->GetHpSpell()-GameData::GetInstance()->GetHpSpell());
        GameData::GetInstance()->SetManaSpell(static_cast<Player*>(p_player)->GetManaSpell()-GameData::GetInstance()->GetManaSpell());
                GameData::GetInstance()->SetDamageSpell(static_cast<Player*>(p_player)->GetDmgSpell()-GameData::GetInstance()->GetDamageSpell());
                        GameData::GetInstance()->SetSpeedSpell(static_cast<Player*>(p_player)->GetSpeedSpell()-GameData::GetInstance()->GetSpeedSpell());
                GameData::GetInstance()->SetHpX2(static_cast<Player*>(p_player)->GetHPX2()-GameData::GetInstance()->GetHpX2());
                GameData::GetInstance()->SetManaX2(static_cast<Player*>(p_player)->GetManaX2()-GameData::GetInstance()->GetManaX2());


        if(p_score<GameData::GetInstance()->GetBestScore()||(p_score==GameData::GetInstance()->GetBestScore()&&p_time>=GameData::GetInstance()->GetBestTime()))
            Game::GetInstance()->GetGameStateMachine()->pushState(new GameOverState(blindTex(Game::GetInstance()->GetRenderer()),"gameover",588,60,static_cast<Player*>(p_player)->GetGold(),static_cast<Player*>(p_player)->GetGem(),p_score,p_time,3));
        else Game::GetInstance()->GetGameStateMachine()->pushState(new GameOverState(blindTex(Game::GetInstance()->GetRenderer()),"best_achievement",600,200,static_cast<Player*>(p_player)->GetGold(),static_cast<Player*>(p_player)->GetGem(),p_score,p_time,3));
    }
    else if(runTime==false)
    {
        runTime=true;
        p_start_loop=SDL_GetTicks();
    }

    Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
    int x_pl=static_cast<Player*>(p_player)->GetPosInMapX();
    int y_pl=static_cast<Player*>(p_player)->GetPosInMapY();
    int speed_pl=static_cast<Player*>(p_player)->GetSpeed();

    if(runTime==true)
        p_time+=SDL_GetTicks()-p_start_loop;

    if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE)||(HandleInput::GetInstance()->GetMouse(0)&&vec->GetX()>955&&vec->GetX()<1015&&vec->GetY()>10&&vec->GetY()<70))
    {
        runTime=false;
        Game::GetInstance()->GetGameStateMachine()->pushState(new PauseState(blindTex(Game::GetInstance()->GetRenderer()),3));
    }

    p_start_loop=SDL_GetTicks();

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


    if(y_pl>1000)
    {
        static_cast<Player*>(p_player)->SetHP(-1-p_score/1000);
        static_cast<Player*>(p_player)->push_hp_lose(-1-p_score/1000);
    }

    for(GameObject* i: p_grass_1)
    {
        if(TypeCollission(p_player,i)==1)
        {
            int t=static_cast<Grass*>(i)->GetFirY();
            static_cast<Player*>(p_player)->fixDown(t);
            static_cast<Player*>(p_player)->SetJumped(false);
            static_cast<Player*>(p_player)->SetTimeJump(0);
            break;
        }
    }

    p_darts=static_cast<Player*>(p_player)->GetDarts();
    p_eskill_player=static_cast<Player*>(p_player)->GetEskill();

    for(GameObject* i:p_darts)
    {
        i->update();
    }

    for(GameObject* i:p_eskill_player)
        i->update();


    for(int i=0; i<p_animation.size(); i++)
    {
        if(static_cast<Animation*>(p_animation[i])->GetTime()>=4)
        {
            p_animation[i]->clean();
            p_animation.erase(p_animation.begin()+i);
            i--;
        }
    }
    for(GameObject* i:p_animation)
        i->update();

    count_boss_max=std::min(p_score/100,30);
    if(p_boss.size()<count_boss_max)
    {
        int k=rand()%1800+50;
        p_boss.push_back(new Boss(new LoaderParams(k,0,110,150,"boss_nor"),x_pl,y_pl,10000,20,3));

    }
    if(p_soldiers.size()<30-count_boss_max)
    {
        int k=rand()%1900+50;
        p_soldiers.push_back(new Soldier(new LoaderParams(k,0,60,75,"fide1"),x_pl,y_pl,100,3,3));
    }
    int t=Pos_Map_3(x_pl,y_pl,50,75);
    int dmg_pl=static_cast<Player*>(p_player)->GetDamage();





    //update soldier
    for(GameObject* i:p_soldiers)
    {
        static_cast<Soldier*>(i)->SetPlayerPos(Pos_Map[ {static_cast<Soldier*>(i)->GetPosMap(),t}]);
        static_cast<Soldier*>(i)->SetMapX(x_pl);
        static_cast<Soldier*>(i)->SetMapY(y_pl);
        i->update();
    }
    for(GameObject* i:p_soldiers)
    {
        if(Collission(i,p_player)&&static_cast<Soldier*>(i)->GetATK())
        {
            int k=rand()%100+50;
            int t=static_cast<Soldier*>(i)->GetDmg();
            static_cast<Player*>(p_player)->SetHP(-t*k/100);
            static_cast<Player*>(p_player)->push_hp_lose(-t*k/100);
        }
    }
    for(int i=0; i<p_soldiers.size(); i++)
    {
        if(static_cast<Soldier*>(p_soldiers[i])->GetHP()<=0)
        {
            p_score++;
            Vector2D tmp=static_cast<SDLGameObject*>(p_soldiers[i])->GetPos();
            p_animation.push_back(new Animation(new LoaderParams(tmp.GetX()-5,tmp.GetY()+10,60,60,"smoke"),4));
            int t=rand()%100+1;
            if(t==1)p_item.push_back(new Item(new LoaderParams(static_cast<Soldier*>(p_soldiers[i])->GetPosInMapX(),static_cast<Soldier*>(p_soldiers[i])->GetPosInMapY(),35,44,"gem"),x_pl,y_pl,"gem",3));
            else if(t>=2&&t<=51)p_item.push_back(new Item(new LoaderParams(static_cast<Soldier*>(p_soldiers[i])->GetPosInMapX(),static_cast<Soldier*>(p_soldiers[i])->GetPosInMapY(),35,38,"gold"),x_pl,y_pl,"gold",3));

            p_soldiers[i]->clean();
            p_soldiers.erase(p_soldiers.begin()+i);
            i--;
        }
    }
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

                p_darts[i]->clean();
                p_darts.erase(p_darts.begin()+i);
                i--;

                int t=rand()%10+95;
                static_cast<Soldier*>(p_soldiers[j])->SetHP(-(dmg_pl)*t/100);
                static_cast<Soldier*>(p_soldiers[j])->push_hp_lose(-(dmg_pl)*t/100);
                break;
            }
        }
    }
    for(int i=0; i<p_eskill_player.size(); i++)
    {
        for(int j=0; j<p_soldiers.size(); j++)
        {

            if(Collission(p_eskill_player[i],p_soldiers[j])&& static_cast<Soldier*>(p_soldiers[j])->GetHP()>0)
            {
                int t=rand()%20+90;
                static_cast<Soldier*>(p_soldiers[j])->SetHP(-dmg_pl*t/10);
                static_cast<Soldier*>(p_soldiers[j])->push_hp_lose(-dmg_pl*t/10);
                break;
            }
        }
    }


    //update boss
    for(int i=0; i<p_boss.size(); i++)
    {
        static_cast<Boss*>(p_boss[i])->SetEskill(p_eskill_boss[i]);
        static_cast<Boss*>(p_boss[i])->SetPlayerPos(Pos_Map[ {static_cast<Boss*>(p_boss[i])->GetPosMap(),t}]);
        static_cast<Boss*>(p_boss[i])->SetMapX(x_pl);
        static_cast<Boss*>(p_boss[i])->SetMapY(y_pl);
        static_cast<Boss*>(p_boss[i])->update();

        p_eskill_boss[i]=static_cast<Boss*>(p_boss[i])->GetEskill();
        for(GameObject* j:p_eskill_boss[i])
            j->update();

        for(int j=0; j<p_darts.size(); j++)
        {
            if(Collission(p_darts[j],p_boss[i]))
            {
                if(GameData::GetInstance()->GetLevelDart()==3)
                {
                    Vector2D tmp=static_cast<SDLGameObject*>(p_boss[i])->GetPos();
                    p_animation.push_back(new Animation(new LoaderParams(tmp.GetX()+30,tmp.GetY()+70,50,50,"big_bang"),4));
                    ManageSound::GetInstance()->playSound("dart3",0);
                }
                else ManageSound::GetInstance()->playSound("atk2",0);
                ManageSound::GetInstance()->playSound("atk2",0);

                p_darts[j]->clean();
                p_darts.erase(p_darts.begin()+j);
                j--;

                int t=rand()%10+95;
                static_cast<Boss*>(p_boss[i])->SetHP(-(dmg_pl)*t/100);
                static_cast<Boss*>(p_boss[i])->push_hp_lose(-(dmg_pl)*t/100);
            }
        }

        for(int j=0; j<p_eskill_player.size(); j++)
        {
            if(Collission(p_eskill_player[j],p_boss[i]))
            {
                int t=rand()%20+90;
                static_cast<Boss*>(p_boss[i])->SetHP(-dmg_pl*t/10);
                static_cast<Boss*>(p_boss[i])->push_hp_lose(-dmg_pl*t/10);
            }
        }
        for(int j=0; j<p_eskill_boss[i].size(); j++)
        {
            if(Collission(p_eskill_boss[i][j],p_player))
            {
                int t=rand()%20+90;
                int k=static_cast<Boss*>(p_boss[i])->GetDmg();
                static_cast<Player*>(p_player)->SetHP(-k*t/20);
                static_cast<Player*>(p_player)->push_hp_lose(-k*t/20);
            }
            if(Collission(p_boss[i],p_player)&&static_cast<Boss*>(p_boss[i])->GetATK())
            {
                int t=rand()%20+90;
                int k=static_cast<Boss*>(p_boss[i])->GetDmg();
            static_cast<Player*>(p_player)->SetHP(-k*t/100);
            static_cast<Player*>(p_player)->push_hp_lose(-k*t/100);
            }
        }
        if(static_cast<Boss*>(p_boss[i])->GetHP()<=0)
        {
            p_score+=10;
            Vector2D tmp=static_cast<SDLGameObject*>(p_boss[i])->GetPos();
            p_animation.push_back(new Animation(new LoaderParams(tmp.GetX()-5,tmp.GetY()+10,60,60,"smoke"),4));
            //int t=rand()%100+1;
            //if(t==1)p_item.push_back(new Item(new LoaderParams(static_cast<Soldier*>(p_soldiers[i])->GetPosInMapX(),static_cast<Soldier*>(p_soldiers[i])->GetPosInMapY(),35,44,"gem"),x_pl,y_pl,"gem"));
            //else if(t>=2&&t<=100)p_item.push_back(new Item(new LoaderParams(static_cast<Soldier*>(p_soldiers[i])->GetPosInMapX(),static_cast<Soldier*>(p_soldiers[i])->GetPosInMapY(),35,38,"gold"),x_pl,y_pl,"gold"));
            for(int j=1; j<=5; j++)
            {
                int t=rand()%2;
                if(t==0)p_item.push_back(new Item(new LoaderParams(static_cast<Boss*>(p_boss[i])->GetPosInMapX()+40*j-100,static_cast<Boss*>(p_boss[i])->GetPosInMapY(),35,44,"gem"),x_pl,y_pl,"gem",3));
                else p_item.push_back(new Item(new LoaderParams(static_cast<Boss*>(p_boss[i])->GetPosInMapX()+40*j-100,static_cast<Boss*>(p_boss[i])->GetPosInMapY(),35,38,"gold"),x_pl,y_pl,"gold",3));
            }

            p_boss[i]->clean();
            p_boss.erase(p_boss.begin()+i);
            i--;
        }
    }

    for(int i=0; i<p_eskill_boss.size(); i++)
    {
        for(int j=0; j<p_eskill_boss[i].size(); j++)
        {
            if(static_cast<Eskill*>(p_eskill_boss[i][j])->GetTime()>=8)
            {
                p_eskill_boss[i][j]->clean();
                p_eskill_boss[i].erase(p_eskill_boss[i].begin()+j);
                j--;
            }
        }
    }




    for(int i=0; i<p_item.size(); i++)
    {
        if(Collission(p_player,p_item[i]))
        {
            if(static_cast<Item*>(p_item[i])->GetID()=="gold")
            {
                ManageSound::GetInstance()->playSound("collect_gold",0);
                static_cast<Player*>(p_player)->SetGold(1);
            }
            else if(static_cast<Item*>(p_item[i])->GetID()=="gem")
            {
                ManageSound::GetInstance()->playSound("collect_gem",0);
                static_cast<Player*>(p_player)->SetGem(1);
            }

            p_item[i]->clean();
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

void PlayState3::render()
{
    ManageTexture::GetInstance()->draw("backg3",0,0,1020,600,Game::GetInstance()->GetRenderer(),true);

    for(GameObject* i:p_grass_1)
        i->draw();

    for(GameObject* i:p_grass_2)
        i->draw();


    for(GameObject* i:p_soldiers)
        i->draw();

    for(GameObject* i:p_boss)
        i->draw();

    p_player->draw();

    for(GameObject* i:p_grass_3)
        i->draw();

    for(GameObject* i:p_darts)
        i->draw();

    for(GameObject* i:p_eskill_player)
        i->draw();

    for(std::vector<GameObject*> i:p_eskill_boss)
    {
        for(GameObject* j:i)
        {
            j->draw();
        }
    }

    for(GameObject* i:p_item)
        i->draw();

    for(GameObject* i:p_animation)
        i->draw();

    ManageTexture::GetInstance()->draw("pause1",955,10,60,65,Game::GetInstance()->GetRenderer(),true);

    ManageFont::GetInstance()->drawTextBlended("font3","Score : "+std::to_string(p_score), {255,255,255,255},
            700,20,Game::GetInstance()->GetRenderer());
    ManageFont::GetInstance()->drawTextBlended("font3","Time : "+ConvertTime(p_time), {255,255,255,255},700,50,Game::GetInstance()->GetRenderer());
}

bool PlayState3::onEnter()
{
    std::vector<std::vector<int>>v= {{},{6,7,28},{7,8,28},{8,9,28},{9,10,28},{10,11,28},
        {12,1,28},{12,13,1,2,28},{13,14,2,3,28},{14,15,3,4,28},{15,16,4,5,28},{16,5,28},
        {17,18,6,7,28},{18,19,7,8,28},{19,20,8,9,28},{20,21,9,10,28},{21,22,10,11,28},
        {23,12,28},{23,24,12,13,28},{24,25,13,14,28},{25,26,14,15,28},{26,27,15,16,28},{27,26,28},
        {17,18,28},{18,19,28},{19,20,28},{20,21,28},{21,22,28},{1,2,3,4,5}
    };

    for(int i=1; i<=28; i++)
    {
        bfs_map(v,i,Pos_Map);
    }
    v.clear();
    for(int i=1; i<=28; i++)Pos_Map[ {i,i}]=i;

    ManageTexture::GetInstance()->load("Image/backg3.png","backg3",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/rock1.png","rock1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/rock.png","rock",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/lava.png","lava",Game::GetInstance()->GetRenderer());

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
    ManageTexture::GetInstance()->load("Image/hp1.png","hp1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/hp2.png","hp2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/mana1.png","mana1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/mana2.png","mana2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/big_bang.png","big_bang",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/boss_atk_1.png","boss_atk_eskill",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_atk_nor.png","boss_atk_nor",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_jumpdown.png","boss_jumpdown",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_jumpup.png","boss_jumpup",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_nor.png","boss_nor",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_run.png","boss_run",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_die.png","boss_die",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/eskill2.png","eskill2",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/fide1.png","fide1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/fide3.png","fide3",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/fide4.png","fide4",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/fide5.png","fide5",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/fide6.png","fide6",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/smoke.png","smoke",Game::GetInstance()->GetRenderer());


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

    ManageTexture::GetInstance()->load("Image/gameover.png","gameover",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/pause_1.png","pause1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/best_achievement.png","best_achievement",Game::GetInstance()->GetRenderer());


    ManageFont::GetInstance()->load("Font/SuperSquadItalic.ttf","font1",30);
    ManageFont::GetInstance()->load("Font/Lora-Bold.ttf","font3",20);
    ManageFont::GetInstance()->load("Font/Fz-Futura-Maxi.ttf","font2",20);



    ManageSound::GetInstance()->load("Audio/boss_atk_nor.mp3","boss_atk_nor",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/atk1.mp3","atk1",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/atk2.mp3","atk2",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/eskill1.mp3","eskill1",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/dart3.mp3","dart3",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/collect_gold.mp3","collect_gold",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/collect_gem.mp3","collect_gem",SOUND_SFX);


    p_grass_1.push_back(new Grass(new LoaderParams(0,1100,2040,100,"rock1"),0));

    p_grass_2.push_back(new Grass(new LoaderParams(190,900,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(190,700,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(510,900,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(510,700,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(830,900,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(830,700,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1150,900,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1150,700,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1470,900,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1470,700,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1790,900,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1790,700,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(350,600,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(350,800,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(350,1000,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(670,600,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(670,800,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(670,1000,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(990,600,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(990,800,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(990,1000,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1310,600,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1310,800,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1310,1000,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1630,600,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1630,800,60,60,"rock"),0));
    p_grass_2.push_back(new Grass(new LoaderParams(1630,1000,60,60,"rock"),0));

    p_grass_3.push_back(new Grass(new LoaderParams(0,1075,2040,25,"lava"),2));

    p_player=new Player(new LoaderParams(190,200,50,75,"nor"));

    std::vector<GameObject*>tmp;
    for(int i=0; i<30; i++)
    {
        p_eskill_boss.push_back(tmp);
    }
    tmp.clear();

    best_score=GameData::GetInstance()->GetBestScore();
    best_time=GameData::GetInstance()->GetBestTime();

    p_start_loop=SDL_GetTicks();
    return true;
}

bool PlayState3::onExit()
{
    for(GameObject* i:p_soldiers)
    {
        i->clean();
    }
    p_soldiers.clear();

    for(GameObject* i:p_boss)
    {
        i->clean();
    }
    p_boss.clear();

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

    for(GameObject* i:p_eskill_player)
    {
        i->clean();
    }
    p_eskill_player.clear();

    for(std::vector<GameObject*> i:p_eskill_boss)
    {
        for(GameObject* j:i)
        {
            j->clean();
        }
        i.clear();
    }
    p_eskill_boss.clear();

    for(GameObject* i:p_item)
    {
        i->clean();
    }
    p_item.clear();

    for(GameObject* i:p_animation)
    {
        i->clean();
    }
    p_animation.clear();


    p_player->clean();

    Pos_Map.clear();


    ManageTexture::GetInstance()->clearFromTexMap("backg3");
    ManageTexture::GetInstance()->clearFromTexMap("rock1");
    ManageTexture::GetInstance()->clearFromTexMap("rock");
    ManageTexture::GetInstance()->clearFromTexMap("lava");

    ManageTexture::GetInstance()->clearFromTexMap("run");
    ManageTexture::GetInstance()->clearFromTexMap("die");
    ManageTexture::GetInstance()->clearFromTexMap("nor");
    ManageTexture::GetInstance()->clearFromTexMap("jumpup");
    ManageTexture::GetInstance()->clearFromTexMap("jumpdown");
    ManageTexture::GetInstance()->clearFromTexMap("santo");
    ManageTexture::GetInstance()->clearFromTexMap("atk");
    ManageTexture::GetInstance()->clearFromTexMap("dart");
    ManageTexture::GetInstance()->clearFromTexMap("dart_2");
    ManageTexture::GetInstance()->clearFromTexMap("dart_3");
    ManageTexture::GetInstance()->clearFromTexMap("eskill");
    ManageTexture::GetInstance()->clearFromTexMap("hp1");
    ManageTexture::GetInstance()->clearFromTexMap("hp2");
    ManageTexture::GetInstance()->clearFromTexMap("mana1");
    ManageTexture::GetInstance()->clearFromTexMap("mana2");
    ManageTexture::GetInstance()->clearFromTexMap("big_bang");

    ManageTexture::GetInstance()->clearFromTexMap("boss_die");
    ManageTexture::GetInstance()->clearFromTexMap("boss_atk_eskill");
    ManageTexture::GetInstance()->clearFromTexMap("boss_atk_nor");
    ManageTexture::GetInstance()->clearFromTexMap("boss_jumpdown");
    ManageTexture::GetInstance()->clearFromTexMap("boss_jumpup");
    ManageTexture::GetInstance()->clearFromTexMap("boss_nor");
    ManageTexture::GetInstance()->clearFromTexMap("boss_run");
    ManageTexture::GetInstance()->clearFromTexMap("eskill2");

    ManageTexture::GetInstance()->clearFromTexMap("fide1");
    ManageTexture::GetInstance()->clearFromTexMap("fide3");
    ManageTexture::GetInstance()->clearFromTexMap("fide4");
    ManageTexture::GetInstance()->clearFromTexMap("fide5");
    ManageTexture::GetInstance()->clearFromTexMap("fide6");
    ManageTexture::GetInstance()->clearFromTexMap("smoke");

    ManageTexture::GetInstance()->clearFromTexMap("gold");
    ManageTexture::GetInstance()->clearFromTexMap("gem");
    ManageTexture::GetInstance()->clearFromTexMap("gold_data");
    ManageTexture::GetInstance()->clearFromTexMap("gem_data");
    ManageTexture::GetInstance()->clearFromTexMap("hp_spell");
    ManageTexture::GetInstance()->clearFromTexMap("mana_spell");
    ManageTexture::GetInstance()->clearFromTexMap("damage_spell");
    ManageTexture::GetInstance()->clearFromTexMap("mana_x2");
    ManageTexture::GetInstance()->clearFromTexMap("hp_x2");
    ManageTexture::GetInstance()->clearFromTexMap("speed_spell");

    ManageTexture::GetInstance()->clearFromTexMap("pause1");
    ManageTexture::GetInstance()->clearFromTexMap("gameover");
    ManageTexture::GetInstance()->clearFromTexMap("best_achievement");



    ManageFont::GetInstance()->clearFromFontMap("font1");
    ManageFont::GetInstance()->clearFromFontMap("font2");
    ManageFont::GetInstance()->clearFromFontMap("font3");

    ManageSound::GetInstance()->clearFromSFXMap("boss_atk_nor");
    ManageSound::GetInstance()->clearFromSFXMap("atk1");
    ManageSound::GetInstance()->clearFromSFXMap("atk2");
    ManageSound::GetInstance()->clearFromSFXMap("eskill1");
    ManageSound::GetInstance()->clearFromSFXMap("dart3");
    ManageSound::GetInstance()->clearFromSFXMap("collect_gold");
    ManageSound::GetInstance()->clearFromSFXMap("collect_gem");

    return true;
}
