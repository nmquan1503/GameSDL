#ifndef _LoaderParams_h_
#define _LoaderParams_h_


#include<iostream>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class LoaderParams
{
public:
    LoaderParams(int x,int y,int w,int h,std::string TexID);
    int GetX() const {return p_x;}
    int GetY() const {return p_y;}
    int GetW() const {return p_w;}
    int GetH() const {return p_h;}
    std::string GetTexID() const {return p_TexID;}
private:
    int p_x;
    int p_y;
    int p_w;
    int p_h;
    std::string p_TexID;
};

#endif // _LoaderParams_h_

