#ifndef _GameState_h_
#define _GameState_h_

#include <string>
#include <iostream>

class GameState
{
public:
    virtual void update()=0;
    virtual void render()=0;
    virtual bool onEnter()=0;
    virtual bool onExit()=0;
    virtual std::string GetStateID()const =0;
};


#endif // _GameState_h_

