#ifndef _SpItem_h_
#define _SpItem_h_

#include "GameObject.h"
#include "ManageFont.h"
#include "Vector2D.h"
#include "ManageTexture.h"

#include <SDL2/SDL.h>

class SpItem : public SDLGameObject
{
private:
    std::string SpID;
    double time;
public:
    SpItem(const LoaderParams* Params,std::string ID);
    int GetTime(){return time;}
    void update();
    void draw();
    void clean();
    void SetPosX(int x){p_pos.SetX(x);}
    std::string GetID(){return SpID;}
};


#endif // _SpItem_h_
