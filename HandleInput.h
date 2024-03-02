#ifndef _HandleInput_h_
#define _HandleInput_h_

#include<vector>
#include<iostream>

#include<SDL2/SDL.h>

#include "Vector2D.h"

class HandleInput
{
private:
    HandleInput(){}
    ~HandleInput(){}
    static HandleInput* Instance;
    std::vector<bool>p_Mouse={false,false,false};
    enum mouse_buttons
    {
        LEFT=0,
        MIDDLE=1,
        RIGHT=2
    };
    Vector2D* p_MousePos=new Vector2D(0,0);
    const Uint8* p_keyState;
public:
    static HandleInput* GetInstance();
    void update();
    void clean();
    void reset();
    bool GetMouse(int butNum){return p_Mouse[butNum];}
    Vector2D* GetMousePos(){return p_MousePos;}
    bool IsKeyDown(SDL_Scancode key);
    bool IsKeyUp(SDL_Scancode key);
   // bool DoubleMouse(int butNum);
};

#endif // _HandleInput_h_
