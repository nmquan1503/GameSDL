
#include "HandleInput.h"
#include "Game.h"

HandleInput* HandleInput::Instance=NULL;

void HandleInput::clean()
{
    ;
}

void HandleInput::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        p_keyState=SDL_GetKeyboardState(NULL);

        if(event.type==SDL_QUIT)
        {
            Game::GetInstance()->quit();
        }

        if(event.type==SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                p_Mouse[LEFT]=true;
            }
            if(event.button.button==SDL_BUTTON_RIGHT)
            {
                p_Mouse[RIGHT]=true;
            }
            if(event.button.button==SDL_BUTTON_MIDDLE)
            {
                p_Mouse[MIDDLE]=true;
            }
        }

        if(event.type==SDL_MOUSEBUTTONUP)
        {
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                p_Mouse[LEFT]=false;
            }
            if(event.button.button==SDL_BUTTON_RIGHT)
            {
                p_Mouse[RIGHT]=false;
            }
            if(event.button.button==SDL_BUTTON_MIDDLE)
            {
                p_Mouse[MIDDLE]=false;
            }
        }

        if(event.type==SDL_MOUSEMOTION)
        {
            p_MousePos->SetX(event.motion.x);
            p_MousePos->SetY(event.motion.y);
        }

    }
}

HandleInput* HandleInput::GetInstance()
{
        if(Instance==NULL)
        {
            Instance=new HandleInput();
        }
        return Instance;
}

bool HandleInput::IsKeyDown(SDL_Scancode key)
{
    if(p_keyState!=NULL)
    {
        if(p_keyState[key]==1)
        {
            return true;
        }
        return false;
    }
    return false;
}

bool HandleInput::IsKeyUp(SDL_Scancode key)
{
    if(p_keyState!=NULL)
    {
        if(p_keyState[key]==0)
        {
            return true;
        }
    }
    return false;
}

void HandleInput::reset()
{
    p_Mouse={false,false,false};
}
