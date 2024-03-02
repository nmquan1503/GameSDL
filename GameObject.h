#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_


#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>

#include "LoaderParams.h"

class GameObject
{
protected:
    GameObject(const LoaderParams* p_Params){}
    virtual ~GameObject(){}
public:
    virtual void draw()=0;
    virtual void update()=0;
    virtual void clean()=0;

};


#endif // _GAMEOBJJECT_H_
