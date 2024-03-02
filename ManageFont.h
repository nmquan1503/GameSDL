#ifndef _ManageFont_h_
#define _ManageFont_h_

#include <map>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Game.h"
#include "ManageTexture.h"

class ManageFont
{
private:
    ManageFont();
    ~ManageFont();
    static ManageFont* Instance=NULL;
    std::map<std::string id,TTF_Font*>Font_Map;
public:
    static ManageFont* GetInstance();
    bool load(std::string fileName,std::string id,int fontsize);
    void drawTextBlended(std::string id,std::string text,SDL_Color color,int x,int y,SDL_Renderer* renderer);
    void clearFromFontMap(std::string id){Font_Map.erase(id);}
};




#endif // _ManageFont_h_
