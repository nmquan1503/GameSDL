#ifndef _Grass_h_
#define _Grass_h_

#include "GameObject.h"
#include "SDL_GameObject.h"
#include "HandleInput.h"
#include "Vector2D.h"
#include "PlayState.h"

class Grass : public SDLGameObject
{
public:
    Grass(const LoaderParams* Params,int Fpls);
    virtual void draw();
    virtual void update();
    virtual void clean();
    int GetFirX(){return fir_x;}
    int GetFirY(){return fir_y;}
    void SetMap_X(int x){pos_in_map_x=x;}
    void SetMap_Y(int y){pos_in_map_y=y;}

    void SetTexID(std::string id){p_TexID=id;}
private:
    int fir_x;
    int fir_y;
    int pos_in_map_x=0;
    int pos_in_map_y=0;
    int p_Fpls;
};




#endif // _Grass_h_
