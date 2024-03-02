#ifndef _MenuBG_h_
#define _MenuBG_h_

#include "GameObject.h"
#include "SDL_GameObject.h"
#include "HandleInput.h"
#include "Vector2D.h"
#include "LoaderParams.h"

class MenuBG : public SDLGameObject
{
public:
    MenuBG(const LoaderParams* Params);
    virtual void draw();
    virtual void update();
    virtual void clean();
};

#endif // _MenuBG_h_
