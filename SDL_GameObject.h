#ifndef _SDLGameObject_h_
#define _SDLGameObject_h_

#include<iostream>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* p_Params);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void drawBG();
    Vector2D GetPos(){return p_pos;}
    int GetW(){return p_w;}
    int GetH(){return p_h;}
    void SetPos(Vector2D pos){p_pos=pos;}
protected:
    Vector2D p_pos;
    Vector2D p_vel;
    Vector2D p_acc;
    int p_w;
    int p_h;
    int p_Frame;
    int p_Row;
    std::string p_TexID;
    bool flip=true;
};

#endif // _SDLGameObject_h_
