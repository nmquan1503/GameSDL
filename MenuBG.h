#ifndef _MenuBG_h_
#define _MenuBG_h_

#include "GameObject.h"
#include "SDL_GameObject.h"
#include "HandleInput.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include "ManageTexture.h"
#include "Game.h"

class MenuBG : public SDLGameObject
{
public:
    MenuBG(const LoaderParams* Params,int Fpls,int max_x);
    virtual void draw();
    virtual void update();
    virtual void clean();
private:
    int p_Fpls;
    int p_max_x;
    int pos_x;
};

#endif // _MenuBG_h_
