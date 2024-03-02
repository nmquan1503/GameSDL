#ifndef _dart_h_
#define _dart_h_

#include "GameObject.h"
#include "SDL_GameObject.h"
#include "HandleInput.h"
#include "Vector2D.h"
#include "PlayState.h"

class Dart : public SDLGameObject
{
public:
    Dart(const LoaderParams* Params,Vector2D fir,Vector2D sec);
    virtual void draw();
    virtual void update();
    virtual void clean();
    int GetTime(){return time;}
private:
    Vector2D fir_pos;
    Vector2D sec_pos;
    int time=0;
};

#endif // _dart_h_
