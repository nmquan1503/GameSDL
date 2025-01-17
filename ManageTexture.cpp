
#include "ManageTexture.h"

ManageTexture* ManageTexture::Instance=NULL;

bool ManageTexture::load(std::string file_name,std::string id,SDL_Renderer* renderer)
{
    SDL_Surface* sf=IMG_Load(file_name.c_str());
    if(sf==0)return false;
    SDL_Texture* tex=SDL_CreateTextureFromSurface(renderer,sf);
    SDL_FreeSurface(sf);
    if(tex!=0)
    {
        TexMap[id]=tex;
        return true;
    }
    return false;
}

bool ManageTexture::loadFromTex(SDL_Texture* tex,std::string id,SDL_Renderer* renderer)
{
    if(tex!=NULL)
    {
        TexMap[id]=tex;
        return true;
    }
    return false;
}

void ManageTexture::draw(std::string id,int x,int y,int w,int h,SDL_Renderer* renderer,bool flip)
{
    SDL_Rect scr;
    SDL_Rect dst;
    scr.x=0;
    scr.y=0;
    scr.w=dst.w=w;
    scr.h=dst.h=h;
    dst.x=x;
    dst.y=y;
    if(flip==true)
    {
        SDL_RenderCopyEx(renderer,TexMap[id],&scr,&dst,0,0,SDL_FLIP_NONE);
    }
    else SDL_RenderCopyEx(renderer,TexMap[id],&scr,&dst,0,0,SDL_FLIP_HORIZONTAL);
}

void ManageTexture:: drawFrame(std::string id,int x,int y,int w,int h,int Frame,int Row,SDL_Renderer* renderer,bool flip)
{
    SDL_Rect scr;
    SDL_Rect dst;
    scr.x=w*Frame;
    scr.y=Row*h;
    scr.w=dst.w=w;
    scr.h=dst.h=h;
    dst.x=x;
    dst.y=y;
    if(flip==true)
    {
        SDL_RenderCopyEx(renderer,TexMap[id],&scr,&dst,0,0,SDL_FLIP_NONE);
    }
    else SDL_RenderCopyEx(renderer,TexMap[id],&scr,&dst,0,0,SDL_FLIP_HORIZONTAL);
}

void ManageTexture::drawFull(std::string id,int x,int y,int w,int h,SDL_Renderer* renderer)
{
    SDL_Rect dst={x,y,w,h};
    SDL_RenderCopy(renderer,TexMap[id],NULL,&dst);
}

void ManageTexture::clearFromTexMap(std::string TexID)
{
    if(TexMap[TexID]!=NULL)
    {
        TexMap.erase(TexID);
    }
}

void ManageTexture::drawXPls(std::string id,int x,int y,int w,int h,int x_pls,SDL_Renderer* renderer)
{
    SDL_Rect scr={x_pls,0,w,h};
    SDL_Rect dst={x,y,w,h};
    SDL_RenderCopy(renderer,TexMap[id],&scr,&dst);
}

ManageTexture* ManageTexture::GetInstance()
{
    if(Instance==NULL)
    {
        Instance=new ManageTexture();
    }
    return Instance;
}
