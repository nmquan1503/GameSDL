#ifndef _GameStateMachine_h_
#define _GameStateMachine_h_

#include "GameState.h"

#include<vector>

class GameStateMachine
{
private:
    std::vector<GameState*>p_gameStates;
public:
    void clearAllState();
    void pushState(GameState* State);
    void changeState(GameState* State);
    void popState();
    void update();
    void render();
};

#endif // _GameStateMachine_h_
