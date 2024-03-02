
#include "OptionsState.h"

std::string OptionsState::p_OptionsID="OPTIONS";

void OptionsState::update()
{
    for(GameObject* i:p_gameObjects)
        i->update();
}

void OptionsState::render()
{
    for(GameObject* i:p_gameObjects)
        i->draw();
}

bool OptionsState::onEnter()
{
    return true;
}

bool OptionsState::onExit()
{
    return true;
}
