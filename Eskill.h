#ifndef _Eskill_h_
#define _Eskill_h_

#include "GameObject.h"
#include "SDL_GameObject.h"
#include "HandleInput.h"
#include "Vector2D.h"
#include "PlayState.h"

class Eskill : public SDLGameObject
{
public:
    Eskill(const LoaderParams* Params,Vector2D fir,Vector2D sec,bool fl);
    virtual void draw();
    virtual void update();
    virtual void clean();
    int GetTime(){return time;}
private:
    Vector2D fir_pos;
    Vector2D sec_pos;
    int time=-1;
};

#endif // _Eskill_h_
