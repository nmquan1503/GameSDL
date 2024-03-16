#include "Player.h"
#include "SDL_GameObject.h"
#include "EspFunction.cpp"


Player::Player(const LoaderParams* p_Params):SDLGameObject(p_Params)
{
    hp_spell=GameData::GetInstance()->GetHpSpell();
    mana_spell=GameData::GetInstance()->GetManaSpell();
    damage_spell=GameData::GetInstance()->GetDamageSpell();
    hp_x2=GameData::GetInstance()->GetHpX2();
    mana_x2=GameData::GetInstance()->GetManaX2();
    speed_spell=GameData::GetInstance()->GetSpeedSpell();

    hp_max=GameData::GetInstance()->GetHpPlayer();
    mana_max=GameData::GetInstance()->GetManaPlayer();
    hp=hp_max;
    mana=mana_max;
    damage=GameData::GetInstance()->GetDamagePlayer();
    speed=GameData::GetInstance()->GetSpeedPlayer();
}

void Player::turnLeft()
{
    flip=false;
    pos_in_map_x-=std::min(speed,p_left_can);
    pos_in_map_x=std::max(0,pos_in_map_x);
    if(pos_in_map_x<485)p_pos.SetX(pos_in_map_x);
    else if(pos_in_map_x>=485 && pos_in_map_x<=1505)p_pos.SetX(485);
    else p_pos.SetX(pos_in_map_x-1020);
}

void Player::turnRight()
{
    flip=true;
    pos_in_map_x+=std::min(speed,p_right_can);
    pos_in_map_x=std::min(1990,pos_in_map_x);
    if(pos_in_map_x<485)p_pos.SetX(pos_in_map_x);
    else if(pos_in_map_x>=485 && pos_in_map_x<=1505)p_pos.SetX(485);
    else p_pos.SetX(pos_in_map_x-1020);
}

void Player::goUp()
{
    pos_in_map_y-=std::min(100,10*(timeJump+3)*(timeJump+3));
    pos_in_map_y=std::max(0,pos_in_map_y);
    if(pos_in_map_y<=262)p_pos.SetY(pos_in_map_y);
    else if(pos_in_map_y>262 && pos_in_map_y<862)p_pos.SetY(262);
    else p_pos.SetY(pos_in_map_y-600);
}

void Player::goDown()
{
    pos_in_map_y+=std::min(10*timeJump*timeJump,p_down_can);
    pos_in_map_y=std::min(1125,pos_in_map_y);
    if(pos_in_map_y<=262)p_pos.SetY(pos_in_map_y);
    else if(pos_in_map_y>262 && pos_in_map_y<862)p_pos.SetY(262);
    else p_pos.SetY(pos_in_map_y-600);
}

void Player::draw()
{
    SDLGameObject::draw();
    ManageTexture::GetInstance()->draw("hp1",0,10,252,45,Game::GetInstance()->GetRenderer(),true);
    ManageTexture::GetInstance()->draw("hp2",48,23,hp*200/hp_max,20,Game::GetInstance()->GetRenderer(),true);
    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(hp)+"/"+std::to_string(hp_max),{255,255,0,255},100,15,Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->draw("mana1",0,55,202,45,Game::GetInstance()->GetRenderer(),true);
    ManageTexture::GetInstance()->draw("mana2",48,68,mana*150/mana_max,20,Game::GetInstance()->GetRenderer(),true);
    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(mana)+"/"+std::to_string(mana_max),{255,255,0,255},80,60,Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->draw("gold_data",350,10,150,50,Game::GetInstance()->GetRenderer(),true);
    ManageTexture::GetInstance()->draw("gem_data",520,10,150,50,Game::GetInstance()->GetRenderer(),true);

    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(gold),{255,255,0,255},400,20,Game::GetInstance()->GetRenderer());
    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(gem),{255,255,0,255},570,20,Game::GetInstance()->GetRenderer());

    ManageTexture::GetInstance()->draw("hp_spell",960,80,55,55,Game::GetInstance()->GetRenderer(),true);
    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(hp_spell),{255,255,0,255},982,110,Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->draw("mana_spell",960,145,55,55,Game::GetInstance()->GetRenderer(),true);
    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(mana_spell),{255,255,0,255},982,175,Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->draw("speed_spell",960,210,55,55,Game::GetInstance()->GetRenderer(),true);
    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(damage_spell),{255,255,0,255},982,240,Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->draw("hp_x2",900,80,55,55,Game::GetInstance()->GetRenderer(),true);
    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(hp_x2),{255,255,0,255},922,110,Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->draw("mana_x2",900,145,55,55,Game::GetInstance()->GetRenderer(),true);
    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(mana_x2),{255,255,0,255},922,175,Game::GetInstance()->GetRenderer());
    ManageTexture::GetInstance()->draw("damage_spell",900,210,55,55,Game::GetInstance()->GetRenderer(),true);
    ManageFont::GetInstance()->drawTextBlended("font2",std::to_string(damage_spell),{255,255,0,255},922,240,Game::GetInstance()->GetRenderer());

    for(int i:hp_lose)
    {
        int t1=rand()%20-10;
        int t2=rand()%8-4;
        ManageFont::GetInstance()->drawTextBlended("font1",std::to_string(i),{255,255,0,255},p_pos.GetX()+p_w/2+t1,p_pos.GetY()-15+t2,Game::GetInstance()->GetRenderer());
    }
    hp_lose.clear();

    for(int i=0;i<p_sp_item.size();i++)
    {
        static_cast<SpItem*>(p_sp_item[i])->SetPosX(60*i+10);
        p_sp_item[i]->draw();
    }
}

void Player::update()
{
    p_vel.SetX(0);
    p_vel.SetY(0);

    for(int i=0;i<p_sp_item.size();i++)
        p_sp_item[i]->update();

    for(int i=0;i<p_sp_item.size();i++)
    {
        if(static_cast<SpItem*>(p_sp_item[i])->GetTime()>=10000)
        {
            p_sp_item.erase(p_sp_item.begin()+i);
            i--;
        }
    }

    damage=GameData::GetInstance()->GetDamagePlayer();
    if(checkItem(p_sp_item,"hp_x2")==false)
    {
        hp_max=GameData::GetInstance()->GetHpPlayer();
        hp=std::min(hp,hp_max);
    }
    if(checkItem(p_sp_item,"mana_x2")==false)
    {
        mana_max=GameData::GetInstance()->GetManaPlayer();
        mana=std::min(mana,mana_max);
    }
    speed=GameData::GetInstance()->GetSpeedPlayer();
    for(GameObject* i:p_sp_item)
    {
        std::string tmp=static_cast<SpItem*>(i)->GetID();
        if(tmp=="hp")
            SetHP(10);
        else if(tmp=="mana")
            SetMana(2);
        else if(tmp=="damage")
            damage*=2;
        else if(tmp=="speed")
            speed*=2;
    }




    if(hp<=0)
    {
        p_h=95;
        p_w=60;
        if(p_Frame<3)p_Frame=timeDie;
        else
            p_Frame=4;
        timeDie++;
        p_TexID="die";
    }
    else
    {
        if(p_down_can!=0&&!p_IsJump&&!p_fly)
        {
            p_Jumped=true;
            if(timeJump==-6)
            {
                timeJump=0;
            }
        }
        handle();
        SDLGameObject::update();
        for(int i=0; i<p_Darts.size(); i++)
        {
            if(static_cast<Dart*>(p_Darts[i])->GetTime()==8)p_Darts.erase(p_Darts.begin()+i);
        }
        for(int i=0; i<p_Eskill.size(); i++)
        {
            if(static_cast<Dart*>(p_Eskill[i])->GetTime()==8)p_Eskill.erase(p_Eskill.begin()+i);
        }

        SetMana(1);
    }
}

void Player::clean()
{
    ;
}

void Player::handle()
{
    Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
    if(HandleInput::GetInstance()->GetMouse(0)&&vec->GetX()>960&&vec->GetX()<1015&&vec->GetY()>80&&vec->GetY()<135)
    {
        if(hp_spell>0)
        {
            int l=p_sp_item.size();
            p_sp_item.push_back(new SpItem(new LoaderParams(10+l*60,120,55,55,"hp_spell"),"hp"));
            hp_spell--;
        }
    }
    else if(HandleInput::GetInstance()->GetMouse(0)&&vec->GetX()>960&&vec->GetX()<1015&&vec->GetY()>145&&vec->GetY()<200)
    {
        if(mana_spell>0)
        {
            int l=p_sp_item.size();
            p_sp_item.push_back(new SpItem(new LoaderParams(10+l*60,120,55,55,"mana_spell"),"mana"));
            mana_spell--;
        }
    }
    else if(HandleInput::GetInstance()->GetMouse(0)&&vec->GetX()>960&&vec->GetX()<1015&&vec->GetY()>210&&vec->GetY()<265)
    {
        if(speed_spell>0)
        {
            int l=p_sp_item.size();
            p_sp_item.push_back(new SpItem(new LoaderParams(10+l*60,120,55,55,"speed_spell"),"speed"));
            speed_spell--;
        }
    }
    else if(HandleInput::GetInstance()->GetMouse(0)&&vec->GetX()>900&&vec->GetX()<955&&vec->GetY()>80&&vec->GetY()<135)
    {
        if(hp_x2>0)
        {
            int l=p_sp_item.size();
            p_sp_item.push_back(new SpItem(new LoaderParams(10+l*60,120,55,55,"hp_x2"),"hp_x2"));
            hp_x2--;
            hp_max*=2;
            hp*=2;
        }
    }
    else if(HandleInput::GetInstance()->GetMouse(0)&&vec->GetX()>900&&vec->GetX()<955&&vec->GetY()>145&&vec->GetY()<200)
    {
        if(mana_x2>0)
        {
            int l=p_sp_item.size();
            p_sp_item.push_back(new SpItem(new LoaderParams(10+l*60,120,55,55,"mana_x2"),"mana_x2"));
            mana_x2--;
            mana_x2*=2;
            mana*=2;
        }
    }
    else if(HandleInput::GetInstance()->GetMouse(0)&&vec->GetX()>900&&vec->GetX()<955&&vec->GetY()>210&&vec->GetY()<265)
    {
        if(damage_spell>0)
        {
            int l=p_sp_item.size();
            p_sp_item.push_back(new SpItem(new LoaderParams(10+l*60,120,55,55,"damage_spell"),"damage"));
            damage_spell--;
        }
    }



    if(HandleInput::GetInstance()->GetMouse(0)&&mana>=3&&(vec->GetX()<=900||vec->GetY()>=265))
    {
        if(vec->GetX()>960&&vec->GetX()<1015&&vec->GetY())
        p_w=60;
        p_Frame=0;
        p_TexID="atk";
        mana-=3;
        if((*vec-p_pos).GetX()>0)flip=true;
        else flip=false;
        if(GameData::GetInstance()->GetLevelDart()==1)
            p_Darts.push_back(new Dart(new LoaderParams(p_pos.GetX()+30,p_pos.GetY()+35,25,25,"dart"),p_pos+Vector2D(20,25),*vec+Vector2D(-14,-14)));
        else if(GameData::GetInstance()->GetLevelDart()==2)
            p_Darts.push_back(new Dart(new LoaderParams(p_pos.GetX()+30,p_pos.GetY()+35,25,25,"dart_2"),p_pos+Vector2D(20,25),*vec+Vector2D(-14,-14)));
        else p_Darts.push_back(new Dart(new LoaderParams(p_pos.GetX()+30,p_pos.GetY()+35,35,35,"dart_3"),p_pos+Vector2D(20,25),*vec+Vector2D(-14,-14)));
        ManageSound::GetInstance()->playSound("atk1",0);
    }
    else if(HandleInput::GetInstance()->GetMouse(2)&&mana>=150)
    {
        mana-=150;
        p_Frame=0;
        p_w=60;
        p_TexID="atk";
        int xp=0;
        if((*vec-p_pos).GetX()>0)
        {
            flip=true;
            xp=10;
        }
        else
        {
            xp=-220;
            flip=false;
        }
        p_Eskill.push_back(new Eskill(new LoaderParams(p_pos.GetX()+xp,p_pos.GetY(),270,100,"eskill"),p_pos+Vector2D(20,25),*vec+Vector2D(-14,-14),flip));
        ManageSound::GetInstance()->playSound("eskill1",0);
    }
    else
    {
        if(p_IsJump)
        {
            p_Frame=0;
            p_TexID="jumpup";
            goUp();
            timeJump--;
            p_w=60;
            if(timeJump==-3)
            {
                p_IsJump=false;
                p_fly=true;
                timeJump=-4;
            }
            if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_RIGHT))
            {
                turnRight();
            }
            else if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_LEFT))
            {
                turnLeft();
            }
        }
        else if(timeJump<-3)
        {
            p_TexID="santo";
            p_Frame=(++p_Frame)%2;
            timeJump--;
            if(timeJump==-6)
            {
                timeJump=0;
                p_Jumped=true;
                p_fly=false;
            }
            if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_RIGHT))
            {
                turnRight();
            }
            else if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_LEFT))
            {
                turnLeft();
            }
        }
        else if(p_Jumped)
        {
            p_Frame=0;
            p_TexID="jumpdown";
            timeJump++;
            goDown();
            if(p_down_can==0)
            {
                p_Jumped=false;
                timeJump=0;
            }
            if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_RIGHT))
            {
                turnRight();
            }
            else if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_LEFT))
            {
                turnLeft();
            }
        }
        else
        {
            if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_RIGHT))
            {
                p_w=50;
                p_TexID="run";
                turnRight();
                p_Frame=(++p_Frame)%5;
                if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_UP))
                {
                    p_TexID="jumpup";
                    p_w=60;
                    p_IsJump=true;
                }
            }
            else if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_LEFT))
            {
                p_w=50;
                p_TexID="run";
                turnLeft();

                p_Frame=(++p_Frame)%5;
                if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_UP))
                {
                    p_Frame=0;
                    p_TexID="jumpup";
                    p_w=60;
                    p_IsJump=true;
                }
            }
            else if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_UP))
            {
                p_Frame=0;
                p_TexID="jumpup";
                p_w=60;
                p_IsJump=true;
            }
            else
            {
                p_w=50;
                p_TexID="nor";
                p_Frame=(++p_Frame)%2;
            }
        }
    }
}
void Player::fixDown(int view)
{
    pos_in_map_y=view-75;
    if(pos_in_map_y<=262)p_pos.SetY(pos_in_map_y);
    else if(pos_in_map_y>262 && pos_in_map_y<862)p_pos.SetY(262);
    else p_pos.SetY(pos_in_map_y-600);
}

/*void Player::fixRight(int view)
{
    pos_in_map_x=view-60;
    if(pos_in_map_x<=480)p_pos.SetX(pos_in_map_x);
    else if(pos_in_map_x>480 && pos_in_map_x<1500)p_pos.SetX(480);
    else p_pos.SetX(pos_in_map_x-1020);
}

void Player::fixLeft(int view)
{
    pos_in_map_x=view;
    if(pos_in_map_x<=480)p_pos.SetX(pos_in_map_x);
    else if(pos_in_map_x>480 && pos_in_map_x<1500)p_pos.SetX(480);
    else p_pos.SetX(pos_in_map_x-1020);
}*/
