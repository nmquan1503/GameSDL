#ifndef _NPC_h_
#define _NPC_h_

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "LoaderParams.h"
#include "ManageTexture.h"
#include "ManageFont.h"
#include "HandleInput.h"
#include "Game.h"
#include "Vector2D.h"
#include "SDL_GameObject.h"
#include "GameObject.h"

#include <iostream>
#include <vector>
#include <string>

/*class NPC
{
private:
    bool flip=true;
    std::string p_TexID;
    std::string p_FontID;
    int p_x=0;int p_y=945;
    int pos_in_map_x;
    int pos_in_map_y;
    int p_w;int p_h;
    std::vector<std::string>text;
    std::vector<std::string>selection;
    bool pointed=false;
    bool talk=false;
    int comment=-1;
    int commentSize;
    int p_Frame=0;
public:
    NPC(int x,int y,int w,int h,std::string TexID,std::string FontID);
    void update();
    void clean();
    void draw();
    void handle();
    void SetPosInMapX(int x){pos_in_map_x=x;}
    void SetPosInMapY(int y){pos_in_map_y=y;}
    bool GetTalk(){return talk;}
};
*/

class NPC : public SDLGameObject
{
private:
    void (*p_callback)();
    bool p_Released;

    int pos_in_map_x;
    int pos_in_map_y;

    bool canTalk=true;

    bool p_point=false;

    int FramePlus=0;
public:
    NPC(const LoaderParams* p_Params,void (*callback)(),int x,int y);
    virtual void draw();
    virtual void update();
    virtual void clean();

    void SetPosInMap(int x,int y){pos_in_map_x=x,pos_in_map_y=y;}

    void SetCanTalk(bool talk){canTalk=talk;}
    bool GetCanTalk(){return canTalk;}
};

#endif // _NPC_h_
