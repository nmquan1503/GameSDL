#include "GameOverState.h"
#include "EspFunction.cpp";

std::string GameOverState::p_GameOverID="GAMEOVER";
int GameOverState::Map_ID;

GameOverState:: GameOverState(SDL_Texture* tex,std::string texID,int w,int h,int gold,int gem,int score,int time,int ID):p_tex(tex),p_TexID(texID),p_w(w),p_h(h),p_gold(gold),p_gem(gem),p_score(score),p_time(time)
{
    t=0;
    Map_ID=ID;
}

void GameOverState::update()
{
    t++;
    if(t>50)
    {
    for(GameObject* i:p_gameObjects)
        i->update();
    }
}

void GameOverState::render()
{
    SDL_RenderCopy(Game::GetInstance()->GetRenderer(),p_tex,NULL,NULL);
    ManageTexture::GetInstance()->draw(p_TexID,(1020-p_w)/2,(600-p_h)/2-120,p_w,p_h,Game::GetInstance()->GetRenderer(),true);

    if(t>10)
    {
        ManageFont::GetInstance()->drawTextBlended("font3","You got:",{255,255,0,255},380,(600-p_h)/2-120+p_h+20,Game::GetInstance()->GetRenderer());
    }
    if(t>15)
    {
        ManageTexture::GetInstance()->draw("gold",480,(600-p_h)/2-120+p_h+12,35,38,Game::GetInstance()->GetRenderer(),true);
        ManageFont::GetInstance()->drawTextBlended("font3",std::to_string(p_gold),{255,255,0,255},520,(600-p_h)/2-120+p_h+20,Game::GetInstance()->GetRenderer());
    }
    if(t>20)
    {
        ManageTexture::GetInstance()->draw("gem",580,(600-p_h)/2-120+p_h+10,35,44,Game::GetInstance()->GetRenderer(),true);
        ManageFont::GetInstance()->drawTextBlended("font3",std::to_string(p_gem),{255,255,0,255},620,(600-p_h)/2-120+p_h+20,Game::GetInstance()->GetRenderer());
    }
    if(t>25&&p_score>=0)
    {
        ManageFont::GetInstance()->drawTextBlended("font3","Your Achievement:    ",{255,255,0,255},350,(600-p_h)/2-120+p_h+70,Game::GetInstance()->GetRenderer());
        ManageFont::GetInstance()->drawTextBlended("font3","Score: "+std::to_string(p_score),{255,255,0,255},570,(600-p_h)/2-120+p_h+70,Game::GetInstance()->GetRenderer());
        ManageFont::GetInstance()->drawTextBlended("font3","Time: "+ConvertTime(p_time),{255,255,0,255},570,(600-p_h)/2-120+p_h+100,Game::GetInstance()->GetRenderer());
    }
    if(t>30&&p_score>=0)
    {
        if(p_score>GameData::GetInstance()->GetBestScore()||(p_score==GameData::GetInstance()->GetBestScore()&&p_time<GameData::GetInstance()->GetBestTime()))
        {
            ManageFont::GetInstance()->drawTextBlended("font3","Previous best achievement:    ",{255,255,0,255},300,(600-p_h)/2-120+p_h+140,Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font3","Score: "+std::to_string(GameData::GetInstance()->GetBestScore()),{255,255,0,255},620,(600-p_h)/2-120+p_h+140,Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font3","Time: "+ConvertTime(GameData::GetInstance()->GetBestTime()),{255,255,0,255},620,(600-p_h)/2-120+p_h+170,Game::GetInstance()->GetRenderer());
        }
        else
        {
            ManageFont::GetInstance()->drawTextBlended("font3","Best achievement:    ",{255,255,0,255},350,(600-p_h)/2-120+p_h+140,Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font3","Score: "+std::to_string(GameData::GetInstance()->GetBestScore()),{255,255,0,255},570,(600-p_h)/2-120+p_h+140,Game::GetInstance()->GetRenderer());
            ManageFont::GetInstance()->drawTextBlended("font3","Time: "+ConvertTime(GameData::GetInstance()->GetBestTime()),{255,255,0,255},570,(600-p_h)/2-120+p_h+170,Game::GetInstance()->GetRenderer());
        }
    }
    if(t>40)
    {
     for(GameObject* i:p_gameObjects)
        i->draw();
    }
}

bool GameOverState::onEnter()
{
    //Game::GetInstance()->GetGameStateMachine()->clearAllBefore();
   //ManageTexture::GetInstance()->load("Image/gameover.png","gameover",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_restart.png","restart",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/menu_home.png","home",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/gold.png","gold",Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->load("Image/gem.png","gem",Game::GetInstance()->GetRenderer());


    ManageFont::GetInstance()->load("Font/SuperSquadItalic.ttf","font1",25);
    ManageFont::GetInstance()->load("Font/Fz-Futura-Maxi.ttf","font2",20);
    ManageFont::GetInstance()->load("Font/Lora-Bold.ttf","font3",20);


    if(p_score>=0)
    {
        p_gameObjects.push_back(new MenuButton(new LoaderParams(250,(600-p_h)/2-80+p_h+180,250,60,"restart"),p_toRestart));
        p_gameObjects.push_back(new MenuButton(new LoaderParams(520,(600-p_h)/2-80+p_h+180,250,60,"home"),p_toHome));
    }
    else
    {
        p_gameObjects.push_back(new MenuButton(new LoaderParams(250,(600-p_h)/2-80+p_h+50,250,60,"restart"),p_toRestart));
        p_gameObjects.push_back(new MenuButton(new LoaderParams(520,(600-p_h)/2-80+p_h+50,250,60,"home"),p_toHome));
    }

    return true;
}

bool GameOverState::onExit()
{
    for(GameObject* i:p_gameObjects)
        i->clean();
    p_gameObjects.clear();
    ManageTexture::GetInstance()->clearFromTexMap(p_TexID);
    ManageTexture::GetInstance()->clearFromTexMap("restart");
    ManageTexture::GetInstance()->clearFromTexMap("home");
    ManageTexture::GetInstance()->clearFromTexMap("gold");
    ManageTexture::GetInstance()->clearFromTexMap("gem");

    ManageFont::GetInstance()->clearFromFontMap("font1");
    ManageFont::GetInstance()->clearFromFontMap("font2");
    ManageFont::GetInstance()->clearFromFontMap("font3");

    return true;
}

void GameOverState::p_toHome()
{
    Game::GetInstance()->GetGameStateMachine()->clearAllState();
    Game::GetInstance()->GetGameStateMachine()->changeState(new MenuState());
}
void GameOverState::p_toRestart()
{
    Game::GetInstance()->GetGameStateMachine()->clearAllState();
    if(Map_ID==1)
        Game::GetInstance()->GetGameStateMachine()->changeState(new PlayState());
    else if(Map_ID==3)
        Game::GetInstance()->GetGameStateMachine()->changeState(new PlayState3());
}
