
#include "Grass.h"
#include "SDL_GameObject.h"
#include "Vector2D.h"

Grass::Grass(const LoaderParams* Params,int Fpls):SDLGameObject(Params)
{
    fir_x=Params->GetX();
    fir_y=Params->GetY();
    p_Fpls=Fpls;
}

void Grass::draw()
{
    SDLGameObject::draw();
}

void Grass::update()
{
    p_vel.SetX(0);
    p_vel.SetY(0);
    //handle();

    p_Frame=(p_Frame+p_Fpls)%2;
    if(pos_in_map_x<=485)
    {
        p_pos.SetX(fir_x);
    }
    else if(pos_in_map_x>485 &&pos_in_map_x<1505)
    {
        p_pos.SetX(485-(pos_in_map_x-fir_x));
    }
    else
    {
        p_pos.SetX(fir_x-1020);
    }

    if(pos_in_map_y<=262)
    {
        p_pos.SetY(fir_y);
    }
    else if(pos_in_map_y>262&&pos_in_map_y<862)
    {
        p_pos.SetY(262-(pos_in_map_y-fir_y));
    }
    else {
        p_pos.SetY(fir_y-600);
    }

    SDLGameObject::update();

}

void Grass::handle()
{
   /* if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_LEFT) && p_pos.GetX()<fir_x)
    {
        p_vel.SetX(std::min(25,(int)(fir_x-p_pos.GetX())));
    }
    else if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_RIGHT) && p_pos.GetX()>fir_x-1020)
    {
        p_vel.SetX(std::min(-25,(int)(fir_x-p_pos.GetX())));
    }
    else if(HandleInput::GetInstance()->IsKeyDown(SDL_SCANCODE_UP) && p_pos.GetY()<fir_y+600)
    {
        p_vel.SetY(25);
    }*/
}
