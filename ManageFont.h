#ifndef _ManageFont_h_
#define _ManageFont_h_

#include <map>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Game.h"
#include "ManageTexture.h"

class ManageFont
{
private:
    ManageFont();
    ~ManageFont();
    static ManageFont* Instance;
    std::map<std::string ,TTF_Font*>Font_Map;
public:
    static ManageFont* GetInstance();
    bool load(std::string fileName,std::string id,int fontsize);
    void drawTextBlended(std::string id,std::string text,SDL_Color color,int x,int y,SDL_Renderer* renderer);
    void drawInfo(std::string id,std::string text,SDL_Color color,int x,int y,int w_max,SDL_Renderer* renderer);
    void clearFromFontMap(std::string id){Font_Map.erase(id);}
    SDL_Texture* createTex(std::string id,std::string text,SDL_Color,SDL_Renderer* renderer);
    //void drawTextOnBoard(std::string id,std::string text,SDL_Color color,SDL_Renderer* renderer);
};




#endif // _ManageFont_h_
