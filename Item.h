
#ifndef _Item_h_
#define _Item_h_

#include <iostream>
#include <string>
#include "tinyxml2.h"

#include "SDL_GameObject.h"
#include "LoaderParams.h"

class Item : public SDLGameObject
{
private:
    int pos_in_map_x;
    int pos_in_map_y;

    int pos_x;
    int pos_y;

    int p_grass_y;


    std::string itemID;

    int timeSpell=0;
public:
    void update();
    void draw();
    void clean();

    void SetMap_X(int x){pos_in_map_x=x;}
    void SetMap_Y(int y){pos_in_map_y=y;}

    int Grass_map1();

    std::string GetID(){return itemID;}
    int GetTimeSpell(){return timeSpell;}

    Item(const LoaderParams* Params,int p_x,int p_y,std::string type);
};


#endif // _Item_h_
