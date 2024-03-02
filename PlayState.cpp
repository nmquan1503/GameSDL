
#include "PlayState.h"


SDL_Texture* blindTex(SDL_Renderer* renderer)
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

void bfs(std::vector<std::vector<int>> v, int t,std::map<std::pair<int,int>,int>&mp)
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

bool Collission(GameObject* p1,GameObject* p2)
{
    int x1=static_cast<SDLGameObject*>(p1)->GetPos().GetX(),y1=static_cast<SDLGameObject*>(p1)->GetPos().GetY(),w1=static_cast<SDLGameObject*>(p1)->GetW(),h1=static_cast<SDLGameObject*>(p1)->GetH();
    int x2=static_cast<SDLGameObject*>(p2)->GetPos().GetX(),y2=static_cast<SDLGameObject*>(p2)->GetPos().GetY(),w2=static_cast<SDLGameObject*>(p2)->GetW(),h2=static_cast<SDLGameObject*>(p2)->GetH();
    if(x1>=x2+w2||x1+w1<=x2||y1+h1<=y2||y2+h2<=y1)return false;
    return true;
}

int Pos(int x,int y)
{
    //int x1=static_cast<Player*>(g)->GetPosInMapX(),y1=static_cast<Player*>(g)->GetPosInMapY();
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
}

void PlayState::update()
{
    if(static_cast<Player*>(p_player)->GetTimeDie()==20)
    {
        Game::GetInstance()->GetGameStateMachine()->pushState(new GameOverState(blindTex(Game::GetInstance()->GetRenderer())));
    }


    if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
    {

        Game::GetInstance()->GetGameStateMachine()->pushState(new PauseState(blindTex(Game::GetInstance()->GetRenderer())));
    }

    if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_SPACE))
    {
        static_cast<Player*>(p_player)->SetPosInMapX(0);
        static_cast<Player*>(p_player)->SetPosInMapY(975);
        Game::GetInstance()->GetGameStateMachine()->pushState(new PlayState2(p_player));
    }

    // for(GameObject* i:p_gameObjects)
    //{
    //    i->update();
    //}

    static_cast<Player*>(p_player)->SetDart(p_darts);

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

    p_player->update();

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


    /* int t=Pos(static_cast<Player*>(p_player)->GetPosInMapX(),static_cast<Player*>(p_player)->GetPosInMapX());
     for(GameObject* i:p_soldiers)
     {
         static_cast<Soldier*>(i)->SetPlayerPos(t);
     }*/

    if(numSoldier<=200&&p_soldiers.size()<20)
    {
        numSoldier++;
        int k=rand()%2040+1;
        p_soldiers.push_back(new Soldier(new LoaderParams(k,0,60,75,"fide1"),static_cast<Player*>(p_player)->GetPosInMapX(),static_cast<Player*>(p_player)->GetPosInMapY()));
    }
    int t=Pos(static_cast<Player*>(p_player)->GetPosInMapX(),static_cast<Player*>(p_player)->GetPosInMapY ());

    for(GameObject* i:p_soldiers)
    {
        static_cast<Soldier*>(i)->SetPlayerPos(Pos_Map[ {static_cast<Soldier*>(i)->GetPosMap(),t}]);
        static_cast<Soldier*>(i)->SetMapX(static_cast<Player*>(p_player)->GetPosInMapX());
        static_cast<Soldier*>(i)->SetMapY(static_cast<Player*>(p_player)->GetPosInMapY());
        i->update();
    }

    for(GameObject* i:p_soldiers)
    {
        if(Collission(i,p_player))
        {
            static_cast<Player*>(p_player)->SetHP(-3);
        }
    }

    for(int i=0; i<p_darts.size(); i++)
    {
        for(int j=0; j<p_soldiers.size(); j++)
        {
            if(Collission(p_darts[i],p_soldiers[j]))
            {
                p_darts.erase(p_darts.begin()+i);
                i--;
                int t=rand()%7+47;
                static_cast<Soldier*>(p_soldiers[j])->SetHP(-t);
                if(static_cast<Soldier*>(p_soldiers[j])->GetHP()<=0)
                {
                    p_soldiers.erase(p_soldiers.begin()+j);
                    j--;
                }
                break;
            }
        }
    }

    for(int i=0; i<p_eskill.size(); i++)
    {
        for(int j=0; j<p_soldiers.size(); j++)
        {
            if(Collission(p_eskill[i],p_soldiers[j]))
            {
                int t=rand()%100+500;
                static_cast<Soldier*>(p_soldiers[j])->SetHP(-t);
                if(static_cast<Soldier*>(p_soldiers[j])->GetHP()<=0)
                {
                    p_soldiers.erase(p_soldiers.begin()+j);
                    j--;
                }
                break;
            }
        }
    }
    for(int i=0;i<p_eskill.size();i++)
    {
        if(static_cast<Eskill*>(p_eskill[i])->GetTime()==8)
        {
            p_eskill.erase(p_eskill.begin()+i);
            i--;
        }
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
}

bool PlayState::onEnter()
{
    std::vector<std::vector<int>> v = {{}, {2}, {1, 3}, {2, 4}, {3, 7}, {4, 8}, {15}, {4, 10, 1, 3}, {13, 9}, {8, 15}, {7, 11, 1}, {12, 7, 1}, {5, 11}, {8, 14, 5}, {13, 6}, {9, 6}};
    for(int i=1; i<=15; i++)
    {
        bfs(v,i,Pos_Map);
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

    ManageTexture::GetInstance()->clearFromTexMap("backg");
    ManageTexture::GetInstance()->clearFromTexMap("run");
    ManageTexture::GetInstance()->clearFromTexMap("nor");
    ManageTexture::GetInstance()->clearFromTexMap("jumpdown");
    ManageTexture::GetInstance()->clearFromTexMap("jumpup");
    ManageTexture::GetInstance()->clearFromTexMap("santo");
    ManageTexture::GetInstance()->clearFromTexMap("atk");
    ManageTexture::GetInstance()->clearFromTexMap("dart");
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


    return true;
}
