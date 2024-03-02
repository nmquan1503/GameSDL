

#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* State)
{
    p_gameStates.push_back(State);
    p_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
    if(p_gameStates.size()!=0)
    {
        if(p_gameStates.back()->onExit())
        {
            delete p_gameStates.back();
            p_gameStates.pop_back();
        }
    }
}

void GameStateMachine::changeState(GameState* State)
{
    if(!p_gameStates.empty())
    {
        if(p_gameStates.back()->GetStateID()==State->GetStateID())return ;
        if(p_gameStates.back()->onExit())
        {
            delete p_gameStates.back();
            p_gameStates.pop_back();
        }
    }
    p_gameStates.push_back(State);
    p_gameStates.back()->onEnter();
}

void GameStateMachine::update()
{
    if(!p_gameStates.empty())
    {
        p_gameStates.back()->update();
    }
}

void GameStateMachine::render()
{
    if(!p_gameStates.empty())
    {
        p_gameStates.back()->render();
    }
}

void GameStateMachine::clearAllState()
{
    while(!p_gameStates.empty())
    {
        GameStateMachine::popState();
    }
}

