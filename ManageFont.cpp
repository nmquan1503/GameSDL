
#include "ManageFont.h"

#include<string.h>

using namespace std;

ManageFont* ManageFont::Instance=NULL;

ManageFont* ManageFont::GetInstance()
{
    if(Instance==NULL)
    {
        Instance=new ManageFont();
    }
    return Instance;
}

ManageFont::ManageFont()
{

}

ManageFont::~ManageFont()
{
    for (std::map<std::string,TTF_Font*>::iterator it =Font_Map.begin();it!=Font_Map.end();++it)
    {
        if (it->second)
        {
            TTF_CloseFont(it->second);
        }
    }
    Font_Map.clear();
}

bool ManageFont::load(std::string fileName,std::string id,int fontsize)
{
    TTF_Font* font=TTF_OpenFont(fileName.c_str(),fontsize);
    if(font==NULL)
    {
        std::cout<<"ErrorFont:"<<TTF_GetError();
        return false;
    }
    Font_Map[id]=font;
    return true;
}

void ManageFont::drawTextBlended(std::string id,std::string text,SDL_Color color,int x,int y,SDL_Renderer* renderer)
{
    SDL_Surface* sur= TTF_RenderText_Blended(Font_Map[id],text.c_str(),color);
    SDL_Texture* tex=SDL_CreateTextureFromSurface(renderer,sur);
    int w,h;
    SDL_QueryTexture(tex,NULL,NULL,&w,&h);
    SDL_Rect dst={x,y,w,h};
    SDL_RenderCopy(renderer,tex,NULL,&dst);
    SDL_FreeSurface(sur);
    SDL_DestroyTexture(tex);
}

SDL_Texture* ManageFont::createTex(std::string id,std::string text,SDL_Color color,SDL_Renderer* renderer)
{
    SDL_Surface* sur= TTF_RenderText_Blended(Font_Map[id],text.c_str(),color);
    SDL_Texture* tex=SDL_CreateTextureFromSurface(renderer,sur);
    SDL_FreeSurface(sur);
    return tex;
}
