#include "Player.h"
#include "SDL_GameObject.h"


Player::Player(const LoaderParams* p_Params):SDLGameObject(p_Params)
{

}

void Player::turnLeft()
{
    flip=false;
    pos_in_map_x-=std::min(15,p_left_can);
    pos_in_map_x=std::max(0,pos_in_map_x);
    if(pos_in_map_x<485)p_pos.SetX(pos_in_map_x);
    else if(pos_in_map_x>=485 && pos_in_map_x<=1505)p_pos.SetX(485);
    else p_pos.SetX(pos_in_map_x-1020);
}

void Player::turnRight()
{
    flip=true;
    pos_in_map_x+=std::min(15,p_right_can);
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
    ManageTexture::GetInstance()->draw("hp2",48,23,hp*2/10,20,Game::GetInstance()->GetRenderer(),true);
    ManageTexture::GetInstance()->draw("mana1",0,55,202,45,Game::GetInstance()->GetRenderer(),true);
    ManageTexture::GetInstance()->draw("mana2",48,68,mana*150/200,20,Game::GetInstance()->GetRenderer(),true);
}

void Player::update()
{
    p_vel.SetX(0);
    p_vel.SetY(0);

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

        mana=std::min(200,++mana);
    }
}

void Player::clean()
{
    ;
}

void Player::handle()
{
    if(HandleInput::GetInstance()->GetMouse(0)&&mana>=3)
    {
        p_w=60;
        p_Frame=0;
        p_TexID="atk";
        mana-=3;
        Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
        if((*vec-p_pos).GetX()>0)flip=true;
        else flip=false;
        p_Darts.push_back(new Dart(new LoaderParams(p_pos.GetX()+30,p_pos.GetY()+35,25,25,"dart"),p_pos+Vector2D(20,25),*vec+Vector2D(-14,-14)));
    }
    else if(HandleInput::GetInstance()->GetMouse(2)&&mana>=150)
    {
        mana-=150;
        p_Frame=0;
        p_w=60;
        p_TexID="atk";
        Vector2D* vec=HandleInput::GetInstance()->GetMousePos();
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
