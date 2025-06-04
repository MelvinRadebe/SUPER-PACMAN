#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H



#include "State.h"

#include <memory>
#include <stack>

using namespace std;


typedef unique_ptr<State> statePtr; /**\typedef a unique pointer to the Game structure, to improve readability */


class StateManager
{
public:
    
    /// Constructor
    StateManager() {}
    
    /// Destructor
    ~StateManager() {}
    
    /// Add a new state to the stack, which is set to become the current state.
    ///
    /// This state will become the new current state in the following cycle of the game loop. The user can specify whether the old state should be removed before adding the new state or keeping the it on the stack so as to return to it later

    void addState(statePtr newState, bool isReplacing = true);
    
    /// Set the current state tobe removed
    void removeState();
    
    /// Add or remove the current state according to the boolean flags set by addState() and removeState()
    void processStateChanges();
    
    /// Get a pointer to the current state

    statePtr& getCurrentState() {return states_.top();}

private:
    stack<statePtr> states_;
    
    statePtr newState_;
    
    bool isAdding_;
    bool isRemoving_;
    bool isReplacing_;
};

#endif
