
#include "PlayState_2.h"
#include "EspFunction.cpp"




std::string PlayState2::p_Play2ID="PLAY2";

int PlayState2::CollisionPlayer(GameObject* g)
{
    int x1=static_cast<Player*>(p_player)->GetPosInMapX(),y1=static_cast<Player*>(p_player)->GetPosInMapY();
    int x2=static_cast<Grass*>(g)->GetFirX(),y2=static_cast<Grass*>(g)->GetFirY(),w2=static_cast<Grass*>(g)->GetW(),h2=static_cast<Grass*>(g)->GetH();
    if(y1+75>y2&&y1<y2+h2&&x1<x2+w2&&x1+50>x2)return 1;
    if(x1<x2+w2&&x1+50>x2+w2)return 2;
    if(x1+50>x2&&x1<x2)return 3;
    return 0;
}


void PlayState2::update()
{
    if(static_cast<Player*>(p_player)->GetTimeDie()==20)
    {
        Game::GetInstance()->GetGameStateMachine()->pushState(new GameOverState(blindTex(Game::GetInstance()->GetRenderer()),"gameover",588,60,static_cast<Player*>(p_player)->GetGold(),static_cast<Player*>(p_player)->GetGem(),-1,-1,1));
    }

    Vector2D* vec=HandleInput::GetInstance()->GetMousePos();

    if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE)||(HandleInput::GetInstance()->GetMouse(0)&&vec->GetX()>955&&vec->GetX()<1015&&vec->GetY()>10&&vec->GetY()<70))
    {

        Game::GetInstance()->GetGameStateMachine()->pushState(new PauseState(blindTex(Game::GetInstance()->GetRenderer()),1));
    }

    if(p_start==false&&p_end==false)
    {
        if(vec->GetX()<=200&&vec->GetY()<=845&&vec->GetY()<=1150 && HandleInput::GetInstance()->GetMouse(0))
        {
            longText=0;
            IsTalking1=true;
        }
    }

    if(IsTalking1==true&&longText>=text1.size()&&HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_SPACE))
    {
        p_start=true;
        IsTalking1=false;
        static_cast<Grass*>(p_grass_3[0])->SetTexID("sugar1");
    }

    if(static_cast<Boss*>(p_boss)->GetHP()<=0)
    {
        p_end=true;
        p_start=false;
        static_cast<Grass*>(p_grass_3[0])->SetTexID("sugar2");
    }
    if(p_end==true)
    {

        if(vec->GetX()<=200&&vec->GetY()<=845&&vec->GetY()<=1150 && HandleInput::GetInstance()->GetMouse(0))
        {
            longText=0;
            IsTalking2=true;
        }
    }
    if(IsTalking2==true&&longText>=text2.size()&&HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_SPACE))
    {
        p_end=false;
        IsTalking2=false;
        win=true;
    }
    if(win==true)
    {
        timeWin++;
    }
    if(timeWin==20)
    {
        Game::GetInstance()->GetGameStateMachine()->pushState(new GameOverState(blindTex(Game::GetInstance()->GetRenderer()),"victory",600,145,static_cast<Player*>(p_player)->GetGold(),static_cast<Player*>(p_player)->GetGem(),-1,-1,1));
    }






    int x_pl=static_cast<Player*>(p_player)->GetPosInMapX();
    int y_pl=static_cast<Player*>(p_player)->GetPosInMapY();


    if(IsTalking1==false && IsTalking2==false)
    {


        static_cast<Player*>(p_player)->SetDart(p_darts);
        //static_cast<Boss*>(p_boss)->SetEskill(p_eskill_boss);

        int t_l=15,t_r=15;
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

        /*  if(p_npc->GetTalk()==false)*/p_player->update();

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
        p_eskill_player=static_cast<Player*>(p_player)->GetEskill();
        //p_eskill_boss=static_cast<Boss*>(p_boss)->GetEskill();

        for(GameObject* i:p_darts)
        {
            i->update();
        }

        for(GameObject* i:p_eskill_player)
            i->update();

        for(int i=0;i<p_animation.size();i++)
        {
            if(static_cast<Animation*>(p_animation[i])->GetTime()>=4)
            {
                p_animation.erase(p_animation.begin()+i);
                i--;
            }
        }

        for(GameObject* i:p_animation)
            i->update();
    }













    if(p_start==true&&p_end==false)
    {

        int t=Pos_Map_2(x_pl,y_pl,50,75);

        //std::cout<<t<<std::endl;

        static_cast<Boss*>(p_boss)->SetEskill(p_eskill_boss);
        static_cast<Boss*>(p_boss)->SetPlayerPos(Pos_Map[ {static_cast<Boss*>(p_boss)->GetPosMap(),t}]);
        static_cast<Boss*>(p_boss)->SetMapX(x_pl);
        static_cast<Boss*>(p_boss)->SetMapY(y_pl);
        static_cast<Boss*>(p_boss)->update();

        p_eskill_boss=static_cast<Boss*>(p_boss)->GetEskill();
        for(GameObject* i:p_eskill_boss)
            i->update();

        //if(Collission(p_player,p_boss))

        for(int i=0; i<p_darts.size(); i++)
        {
            if(Collission(p_darts[i],p_boss))
            {
                if(GameData::GetInstance()->GetLevelDart()==3)
                {
                    Vector2D tmp=static_cast<SDLGameObject*>(p_boss)->GetPos();
                    p_animation.push_back(new Animation(new LoaderParams(tmp.GetX()+30,tmp.GetY()+70,50,50,"big_bang"),4));
                    ManageSound::GetInstance()->playSound("dart3",0);
                }
                else ManageSound::GetInstance()->playSound("atk2",0);
                ManageSound::GetInstance()->playSound("atk2",0);
                p_darts.erase(p_darts.begin()+i);
                i--;
                int t=rand()%7+47;
                static_cast<Boss*>(p_boss)->SetHP(-t);
                static_cast<Boss*>(p_boss)->push_hp_lose(-t);
            }
        }

        for(int i=0; i<p_eskill_player.size(); i++)
        {
            if(Collission(p_eskill_player[i],p_boss))
            {
                int t=rand()%100+500;
                static_cast<Boss*>(p_boss)->SetHP(-t);
                static_cast<Boss*>(p_boss)->push_hp_lose(-t);
            }
        }

        for(int i=0; i<p_eskill_boss.size(); i++)
        {
            if(Collission(p_eskill_boss[i],p_player))
            {
                int t=rand()%10+50;
                static_cast<Player*>(p_player)->SetHP(-t);
                static_cast<Player*>(p_player)->push_hp_lose(-t);
            }
        }
        if(Collission(p_boss,p_player)&&static_cast<Boss*>(p_boss)->GetATK())
        {
            int t=rand()%4+10;
            static_cast<Player*>(p_player)->SetHP(-t);
            static_cast<Player*>(p_player)->push_hp_lose(-t);
        }

    }






    if(static_cast<Boss*>(p_boss)->GetHP()<=0)
    {
        static_cast<Boss*>(p_boss)->SetMapX(x_pl);
        static_cast<Boss*>(p_boss)->SetMapY(y_pl);
        static_cast<Boss*>(p_boss)->update2();
        p_eskill_boss.clear();
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


}

void PlayState2::render()
{
    ManageTexture::GetInstance()->draw("backg2",0,0,1020,600,Game::GetInstance()->GetRenderer(),true);

    for(GameObject* i:p_grass_1)
        i->draw();

    for(GameObject* i:p_grass_2)
        i->draw();

    for(GameObject* i:p_grass_3)
        i->draw();


    p_boss->draw();
    p_player->draw();
    for(GameObject* i:p_darts)
        i->draw();

    for(GameObject* i:p_eskill_player)
        i->draw();
    for(GameObject* i:p_eskill_boss)
        i->draw();

    for(GameObject* i:p_animation)
        i->draw();
    ManageTexture::GetInstance()->draw("pause1",955,10,60,65,Game::GetInstance()->GetRenderer(),true);


    if(IsTalking1==true)
    {
        ManageTexture::GetInstance()->draw("duongtang",100,200,334,400,Game::GetInstance()->GetRenderer(),true);
        longText++;
        std::string tmp=GetPartText(text1,longText);
        drawOnBoard("font1",tmp,Game::GetInstance()->GetRenderer());
        if(longText>=text1.size())
            ManageTexture::GetInstance()->draw("talk1",435,450,150,137,Game::GetInstance()->GetRenderer(),true);
    }
    else if(IsTalking2==true)
    {
        ManageTexture::GetInstance()->draw("duongtang",100,200,334,400,Game::GetInstance()->GetRenderer(),true);
        longText++;
        std::string tmp=GetPartText(text2,longText);
        drawOnBoard("font1",tmp,Game::GetInstance()->GetRenderer());
        if(longText>=text2.size())
            ManageTexture::GetInstance()->draw("talk2",435,450,150,137,Game::GetInstance()->GetRenderer(),true);
    }

}

bool PlayState2::onEnter()
{
    std::vector<std::vector<int>>v= {{},{2,7},{1,7},{7,4},{3,5},{4,6},{5},{1,2,3}};
    for(int i=1; i<=7; i++)
        bfs_map(v,i,Pos_Map);
    for(int i=1; i<=7; i++)Pos_Map[ {i,i}]=i;

    ManageTexture::GetInstance()->load("Image/backg2.png","backg2",Game::GetInstance()->GetRenderer());

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

    ManageTexture::GetInstance()->load("Image/boss_atk_1.png","boss_atk_eskill",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_atk_nor.png","boss_atk_nor",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_jumpdown.png","boss_jumpdown",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_jumpup.png","boss_jumpup",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_nor.png","boss_nor",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_run.png","boss_run",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/boss_die.png","boss_die",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/eskill2.png","eskill2",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/cold1.png","cold1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/cold2.png","cold2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/cold3.png","cold3",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/duongtang.png","duongtang",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/sugar1.png","sugar1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/sugar2.png","sugar2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/talk1.png","talk1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/talk2.png","talk2",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/mai2.png","mai2",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/gameover.png","gameover",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/victory.png","victory",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/pause_1.png","pause1",Game::GetInstance()->GetRenderer());

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
    ManageTexture::GetInstance()->load("Image/big_bang.png","big_bang",Game::GetInstance()->GetRenderer());



    ManageFont::GetInstance()->load("Font/SuperSquadItalic.ttf","font1",30);
    ManageFont::GetInstance()->load("Font/Lora-Bold.ttf","font3",20);
    ManageFont::GetInstance()->load("Font/Fz-Futura-Maxi.ttf","font2",20);





    ManageSound::GetInstance()->load("Audio/boss_atk_nor.mp3","boss_atk_nor",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/atk1.mp3","atk1",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/atk2.mp3","atk2",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/eskill1.mp3","eskill1",SOUND_SFX);
    ManageSound::GetInstance()->load("Audio/SoundPlay2.mp3","soundplay2",SOUND_MUSIC);
    ManageSound::GetInstance()->load("Audio/dart3.mp3","dart3",SOUND_SFX);


    ManageSound::GetInstance()->playMusic("soundplay2",-1);



    p_grass_1.push_back(new Grass(new LoaderParams(0,1050,1240,150,"cold1"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1240,950,200,250,"cold3"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1440,850,200,350,"cold3"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1640,750,200,450,"cold3"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1840,650,200,550,"cold3"),0));

    p_grass_2.push_back(new Grass(new LoaderParams(450,920,600,50,"cold2"),0));

    p_grass_3.push_back(new Grass(new LoaderParams(50,900,80,150,"sugar2"),1));
    p_grass_3.push_back(new Grass(new LoaderParams(0,800,250,250,"mai2"),0));


    p_boss=new Boss(new LoaderParams(900,900,110,150,"boss_nor"),static_cast<Player*>(p_player)->GetPosInMapX(),static_cast<Player*>(p_player)->GetPosInMapY(),2);

//   p_npc=new NPC(new LoaderParams(50,945,50,105,"sugar1"),talk1,0,975);

    return true;

}

bool PlayState2::onExit()
{
    p_boss->clean();
    p_player->clean();

//    p_npc->clean();

    for(GameObject* i:p_grass_1)
        i->clean();
    p_grass_1.clear();

    for(GameObject* i:p_grass_2)
        i->clean();
    p_grass_2.clear();

    for(GameObject* i:p_grass_3)
        i->clean();
    p_grass_3.clear();

    for(GameObject* i:p_darts)
        i->clean();
    p_darts.clear();

    for(GameObject* i:p_eskill_player)
        i->clean();
    p_eskill_player.clear();

    for(GameObject* i:p_eskill_boss)
        i->clean();
    p_eskill_boss.clear();

    ManageSound::GetInstance()->stopMusic();

    ManageTexture::GetInstance()->clearFromTexMap("backg2");
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
    ManageTexture::GetInstance()->clearFromTexMap("boss_die");
    ManageTexture::GetInstance()->clearFromTexMap("boss_atk_eskill");
    ManageTexture::GetInstance()->clearFromTexMap("boss_atk_nor");
    ManageTexture::GetInstance()->clearFromTexMap("boss_jumpdown");
    ManageTexture::GetInstance()->clearFromTexMap("boss_jumpup");
    ManageTexture::GetInstance()->clearFromTexMap("boss_nor");
    ManageTexture::GetInstance()->clearFromTexMap("boss_run");
    ManageTexture::GetInstance()->clearFromTexMap("eskill2");
    ManageTexture::GetInstance()->clearFromTexMap("cold1");
    ManageTexture::GetInstance()->clearFromTexMap("cold2");
    ManageTexture::GetInstance()->clearFromTexMap("cold3");
    ManageTexture::GetInstance()->clearFromTexMap("duongtang");
    ManageTexture::GetInstance()->clearFromTexMap("sugar1");
    ManageTexture::GetInstance()->clearFromTexMap("sugar2");
    ManageTexture::GetInstance()->clearFromTexMap("talk1");
    ManageTexture::GetInstance()->clearFromTexMap("talk2");
    ManageTexture::GetInstance()->clearFromTexMap("mai2");
    ManageTexture::GetInstance()->clearFromTexMap("gameover");
    ManageTexture::GetInstance()->clearFromTexMap("victory");
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


    ManageFont::GetInstance()->clearFromFontMap("font1");
    ManageFont::GetInstance()->clearFromFontMap("font2");
    ManageFont::GetInstance()->clearFromFontMap("font3");



    ManageSound::GetInstance()->clearFromSFXMap("boss_atk_nor");
    ManageSound::GetInstance()->clearFromSFXMap("atk1");
    ManageSound::GetInstance()->clearFromSFXMap("atk2");
    ManageSound::GetInstance()->clearFromSFXMap("eskill1");
    ManageSound::GetInstance()->clearFromMusicMap("soundplay2");
    ManageSound::GetInstance()->clearFromSFXMap("dart3");

    return true;
}
