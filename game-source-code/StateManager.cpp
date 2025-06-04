#include "StateManager.h"
#include <iostream>

void StateManager::addState(statePtr newState, bool isReplacing)
{
   
    isAdding_ = true;
    isReplacing_ = isReplacing;
    newState_ = move(newState);
}

void StateManager::processStateChanges()
{
    if (isRemoving_ && !states_.empty())
    {
     
        states_.pop();
        if (!states_.empty())
            states_.top()->initialise(); // Re-initialize the new top state
        isRemoving_ = false;
    }

    if (isAdding_)
    {
       
        if (!states_.empty())
        {
            if (isReplacing_)
                states_.pop();
        }
        states_.push(move(newState_));
        states_.top()->initialise(); // Initialize the new top state
        isAdding_ = false;
    }
}

void StateManager::removeState()
{
    isRemoving_ = true;
}
