#ifndef _MenuButton_h_
#define _MenuButton_h_

#include "SDL_GameObject.h"
#include "HandleInput.h"
#include "LoaderParams.h"
#include "ManageSound.h"

class MenuButton : public SDLGameObject
{
private:
    enum button_state
    {
        MOUSE_OUT=0,
        MOUSE_OVER=1,
        CLICKED=2
    };
    void(*p_callback)();
    bool p_Released;
    bool p_sound;
public:
    MenuButton(const LoaderParams* p_Params,void (*callback)());
    virtual void draw();
    virtual void update();
    virtual void clean();
    void SetVel(Vector2D vec){p_vel=vec;}
};

#endif // _MenuButton_h_
