
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

    if(p_Fpls==0)
    {
        p_Frame=0;
    }
    else p_Frame=(++p_Frame)%(p_Fpls+1);
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

void Grass::clean()
{
    SDLGameObject::clean();
}
