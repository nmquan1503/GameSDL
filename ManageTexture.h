#ifndef _ManageTexture_
#define _ManageTexture_


#include<iostream>
#include<map>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class ManageTexture
{
private:
    std::map<std::string ,SDL_Texture* >TexMap;
    static ManageTexture* Instance;
    ManageTexture(){}
public:
    static ManageTexture* GetInstance();
    bool load(std::string file_name,std::string id,SDL_Renderer* renderer);
    bool loadFromTex(SDL_Texture* tex,std::string id,SDL_Renderer* renderer);
    void draw(std::string id,int x,int y,int w,int h,SDL_Renderer* renderer,bool flip);
    void drawFrame(std::string id,int x,int y,int w,int h,int Frame,SDL_Renderer* renderer,bool flip);
    void clearFromTexMap(std::string TexID){TexMap.erase(TexID);}
};

#endif // _ManageTexture_
