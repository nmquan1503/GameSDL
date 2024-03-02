#include "InstructionState.h"

std::string InstructionState::p_InsID="INSTRUCTION";

void InstructionState::update()
{
    for(GameObject* i:p_gameObjects)
        i->update();
}

void InstructionState::render()
{
    for(GameObject* i:p_gameObjects)
        i->draw();
}

bool InstructionState::onEnter()
{
    return true;
}

bool InstructionState::onExit()
{
    return true;
}
