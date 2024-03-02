
#include "PlayState_2.h"


SDL_Texture* blindTex2(SDL_Renderer* renderer)
{
    SDL_Surface* screenSurface = SDL_CreateRGBSurface(0, 1020, 600, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenSurface->pixels, screenSurface->pitch);
    Uint32* pixels = static_cast<Uint32*>(screenSurface->pixels);
    int pixelCount = screenSurface->w * screenSurface->h;

    for (int i = 0; i < pixelCount; ++i)
    {
        Uint8* pixel = reinterpret_cast<Uint8*>(&pixels[i]);

        // Lấy giá trị RGBA của pixel
        Uint8 r, g, b, a;
        SDL_GetRGBA(pixels[i], screenSurface->format, &r, &g, &b, &a);

        // Giảm độ sáng (ví dụ giảm 50%)
        r = static_cast<Uint8>(r * 0.5);
        g = static_cast<Uint8>(g * 0.5);
        b = static_cast<Uint8>(b * 0.5);

        // Tạo giá trị RGBA mới
        pixels[i] = SDL_MapRGBA(screenSurface->format, r, g, b, a);
    }
    SDL_Texture* tex=SDL_CreateTextureFromSurface(renderer,screenSurface);
    SDL_FreeSurface(screenSurface);
    return tex;
}

void bfs2(std::vector<std::vector<int>> v, int t,std::map<std::pair<int,int>,int>&mp)
{
    std::vector<int> q;
    q.push_back(t);
    int n = v.size();
    std::vector<bool> visit(n, false);
    std::vector<int> par(n, 0);
    std::vector<bool> check(n, false);
    visit[t] = true;
    while (!q.empty())
    {
        int u = q[0];
        q.erase(q.begin());
        for (int i : v[u])
        {
            if (!visit[i])
            {
                visit[i] = true;
                q.push_back(i);
                par[i] = u;
                if (check[i] == false)
                {
                    std::vector<int> path;
                    for (int v = i; v != t; v = par[v])
                    {
                        path.push_back(v);
                    }
                    path.push_back(t);
                    reverse(path.begin(), path.end());
                    mp[ {t, i}] = path[1];
                    check[i] = true;
                }
            }
        }
    }
}

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

bool Collission2(GameObject* p1,GameObject* p2)
{
    int x1=static_cast<SDLGameObject*>(p1)->GetPos().GetX(),y1=static_cast<SDLGameObject*>(p1)->GetPos().GetY(),w1=static_cast<SDLGameObject*>(p1)->GetW(),h1=static_cast<SDLGameObject*>(p1)->GetH();
    int x2=static_cast<SDLGameObject*>(p2)->GetPos().GetX(),y2=static_cast<SDLGameObject*>(p2)->GetPos().GetY(),w2=static_cast<SDLGameObject*>(p2)->GetW(),h2=static_cast<SDLGameObject*>(p2)->GetH();
    if(x1>=x2+w2||x1+w1<=x2||y1+h1<=y2||y2+h2<=y1)return false;
    return true;
}

int Pos2(int x,int y)
{
    if(x>400&&x<1050&&y+75<=920)return 2;
    if(x>1790&&y+75<=650)return 6;
    if(x>1590&&x<1840&&y+75<=750)return 5;
    if(x>1390&&x<1640&&y+75<=850)return 4;
    if(x>1190&&x<1440&&y+75<=950)return 3;
    if(x<750&&y+75<=1050)return 1;
    return 7;
}

void PlayState2::drawOnBoard(std::string id,std::string text)
{
    SDL_Texture* tex=ManageFont::GetInstance()->createTex(id,text, {0,0,0,255},Game::GetInstance()->GetRenderer());
    int w;
    int h;
    SDL_QueryTexture(tex,NULL,NULL,&w,&h);
    SDL_Surface* sur=IMG_Load("Image/bogoc.png");
    SDL_Texture* tex2=SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(),sur);
    SDL_FreeSurface(sur);
    int x=(1020-w)/2-50;
    int y=300;
    SDL_Rect dst= {x,y,1020-2*x,150};
    SDL_RenderCopy(Game::GetInstance()->GetRenderer(),tex2,NULL,&dst);
    dst= {(1020-w)/2,350,w,h};
    SDL_RenderCopy(Game::GetInstance()->GetRenderer(),tex,NULL,&dst);
}

std::string GetSL(std::string tmp,int k)
{
    if(k>tmp.size())k=tmp.size();
    std::string n="";
    for(int i=0; i<k; i++)n+=tmp[i];
    return n;
}

/*void PlayState2::talk1()
{
    Talking1=true;
//    p_play=new MenuButton(new LoaderParams(450,600,250,60,"menu_home"),start_play);
}
void PlayState2::start_play()
{
    p_start=true;
}*/

void PlayState2::update()
{
    if(static_cast<Player*>(p_player)->GetTimeDie()==20)
    {
        Game::GetInstance()->GetGameStateMachine()->pushState(new GameOverState(blindTex2(Game::GetInstance()->GetRenderer())));
    }


    if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
    {

        Game::GetInstance()->GetGameStateMachine()->pushState(new PauseState(blindTex2(Game::GetInstance()->GetRenderer())));
    }

    if(p_start==false&&p_end==false)
    {
        Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
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
    }

    if(static_cast<Boss*>(p_boss)->GetHP()<=0)
    {
        p_end=true;
        p_start=false;
    }
    if(p_end==true)
    {
        Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
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








    if(IsTalking1==false && IsTalking2==false)
    {


        static_cast<Player*>(p_player)->SetDart(p_darts);
        //static_cast<Boss*>(p_boss)->SetEskill(p_eskill_boss);

        int t_l=15,t_r=15;
        int x1=static_cast<Player*>(p_player)->GetPosInMapX();
        int y1=static_cast<Player*>(p_player)->GetPosInMapY();
        for(GameObject* i:p_grass_1)
        {
            int x2=static_cast<Grass*>(i)->GetFirX(),w2=static_cast<Grass*>(i)->GetW();
            int y2=static_cast<Grass*>(i)->GetFirY(),h2=static_cast<Grass*>(i)->GetH();
            if(y1<y2+h2&&y1+75>y2)
            {
                if(x1-(x2+w2)>=0)t_l=std::min(t_l,x1-(x2+w2));
                if(x2-(x1+50)>=0)t_r=std::min(t_r,x2-(x1+50));
            }
        }
        static_cast<Player*>(p_player)->SetRightCan(t_r);
        static_cast<Player*>(p_player)->SetLeftCan(t_l);

        int t_d=std::min(100,10*static_cast<Player*>(p_player)->GetTimeJump());
        for(GameObject* i:p_grass_1)
        {
            int x2=static_cast<Grass*>(i)->GetFirX(),w2=static_cast<Grass*>(i)->GetW();
            int y2=static_cast<Grass*>(i)->GetFirY();//h2=static_cast<Grass*>(i)->GetH();
            if(x1<x2+w2&&x1+50>x2)
            {
                if(y2-(y1+75)>=0)t_d=std::min(t_d,y2-(y1+75));
            }
        }
        for(GameObject* i:p_grass_2)
        {
            int x2=static_cast<Grass*>(i)->GetFirX(),w2=static_cast<Grass*>(i)->GetW();
            int y2=static_cast<Grass*>(i)->GetFirY();//h2=static_cast<Grass*>(i)->GetH();
            if(x1<x2+w2&&x1+50>x2)
            {
                if(y2-(y1+75)>=0)t_d=std::min(t_d,y2-(y1+75));
            }
        }
        static_cast<Player*>(p_player)->SetDownCan(t_d);

        /*  if(p_npc->GetTalk()==false)*/p_player->update();

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
    }













    if(p_start==true&&p_end==false)
    {

        int t=Pos2(static_cast<Player*>(p_player)->GetPosInMapX(),static_cast<Player*>(p_player)->GetPosInMapY ());


        static_cast<Boss*>(p_boss)->SetEskill(p_eskill_boss);
        static_cast<Boss*>(p_boss)->SetPlayerPos(Pos_Map[ {static_cast<Boss*>(p_boss)->GetPosMap(),t}]);
        static_cast<Boss*>(p_boss)->SetMapX(static_cast<Player*>(p_player)->GetPosInMapX());
        static_cast<Boss*>(p_boss)->SetMapY(static_cast<Player*>(p_player)->GetPosInMapY());
        static_cast<Boss*>(p_boss)->update();

        p_eskill_boss=static_cast<Boss*>(p_boss)->GetEskill();
        for(GameObject* i:p_eskill_boss)
            i->update();

        //if(Collission(p_player,p_boss))

        for(int i=0; i<p_darts.size(); i++)
        {
            if(Collission2(p_darts[i],p_boss))
            {
                p_darts.erase(p_darts.begin()+i);
                i--;
                int t=rand()%7+47;
                static_cast<Boss*>(p_boss)->SetHP(-t);
                static_cast<Boss*>(p_boss)->push_hp_lose(-t);
            }
        }

        for(int i=0; i<p_eskill_player.size(); i++)
        {
            if(Collission2(p_eskill_player[i],p_boss))
            {
                int t=rand()%100+500;
                static_cast<Boss*>(p_boss)->SetHP(-t);
                static_cast<Boss*>(p_boss)->push_hp_lose(-t);
            }
        }

        for(int i=0; i<p_eskill_boss.size(); i++)
        {
            if(Collission2(p_eskill_boss[i],p_player))
            {
                int t=rand()%10+50;
                static_cast<Player*>(p_player)->SetHP(-t);
            }
        }
        if(Collission2(p_boss,p_player)&&static_cast<Boss*>(p_boss)->GetATK())
            static_cast<Player*>(p_player)->SetHP(-3);
    }












    for(GameObject* i: p_grass_1)
    {
        static_cast<Grass*>(i)->SetMap_X(static_cast<Player*>(p_player)->GetPosInMapX());
        static_cast<Grass*>(i)->SetMap_Y(static_cast<Player*>(p_player)->GetPosInMapY());
        i->update();
    }
    for(GameObject* i: p_grass_2)
    {
        static_cast<Grass*>(i)->SetMap_X(static_cast<Player*>(p_player)->GetPosInMapX());
        static_cast<Grass*>(i)->SetMap_Y(static_cast<Player*>(p_player)->GetPosInMapY());
        i->update();
    }
    for(GameObject* i: p_grass_3)
    {
        static_cast<Grass*>(i)->SetMap_X(static_cast<Player*>(p_player)->GetPosInMapX());
        static_cast<Grass*>(i)->SetMap_Y(static_cast<Player*>(p_player)->GetPosInMapY());
        i->update();
    }


    //  p_npc->SetPosInMapX(static_cast<Player*>(p_player)->GetPosInMapX());
    // p_npc->SetPosInMapY(static_cast<Player*>(p_player)->GetPosInMapY());

//    p_npc->update();
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

    //  p_npc->draw();

    p_boss->draw();
    p_player->draw();
    for(GameObject* i:p_darts)
        i->draw();

    for(GameObject* i:p_eskill_player)
        i->draw();
    for(GameObject* i:p_eskill_boss)
        i->draw();


    if(IsTalking1==true)
    {
        longText++;
        std::string tmp=GetSL(text1,longText);
        drawOnBoard("font1",tmp);
    }
    else if(IsTalking2==true)
    {
        longText++;
        std::string tmp=GetSL(text2,longText);
        drawOnBoard("font1",tmp);
    }

}

bool PlayState2::onEnter()
{
    std::vector<std::vector<int>>v= {{},{2,7},{1,7},{7,4},{3,5},{4,6},{5},{1,2,3}};
    for(int i=1; i<=7; i++)
        bfs2(v,i,Pos_Map);
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

    ManageTexture::GetInstance()->load("Image/eskill2.png","eskill2",Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->load("Image/cold1.png","cold1",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/cold2.png","cold2",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/cold3.png","cold3",Game::GetInstance()->GetRenderer());

    //  ManageTexture::GetInstance()->load("Image/sugar1.png","sugar",Game::GetInstance()->GetRenderer());



    ManageFont::GetInstance()->load("Font/SuperSquadItalic.ttf","font1",30);



    p_grass_1.push_back(new Grass(new LoaderParams(0,1050,1240,150,"cold1"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1240,950,200,250,"cold3"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1440,850,200,350,"cold3"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1640,750,200,450,"cold3"),0));
    p_grass_1.push_back(new Grass(new LoaderParams(1840,650,200,550,"cold3"),0));

    p_grass_2.push_back(new Grass(new LoaderParams(450,920,600,50,"cold2"),0));


    p_boss=new Boss(new LoaderParams(900,900,110,150,"boss_nor"),static_cast<Player*>(p_player)->GetPosInMapX(),static_cast<Player*>(p_player)->GetPosInMapY());

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

    ManageTexture::GetInstance()->clearFromTexMap("backg2");
    ManageTexture::GetInstance()->clearFromTexMap("run");
    ManageTexture::GetInstance()->clearFromTexMap("die");
    ManageTexture::GetInstance()->clearFromTexMap("nor");
    ManageTexture::GetInstance()->clearFromTexMap("jumpup");
    ManageTexture::GetInstance()->clearFromTexMap("jumpdown");
    ManageTexture::GetInstance()->clearFromTexMap("santo");
    ManageTexture::GetInstance()->clearFromTexMap("atk");
    ManageTexture::GetInstance()->clearFromTexMap("dart");
    ManageTexture::GetInstance()->clearFromTexMap("eskill");
    ManageTexture::GetInstance()->clearFromTexMap("hp1");
    ManageTexture::GetInstance()->clearFromTexMap("hp2");
    ManageTexture::GetInstance()->clearFromTexMap("mana1");
    ManageTexture::GetInstance()->clearFromTexMap("mana2");
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
    // ManageTexture::GetInstance()->clearFromTexMap("sugar1");


    ManageFont::GetInstance()->clearFromFontMap("font1");

    return true;
}
