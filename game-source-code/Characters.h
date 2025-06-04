#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "State.h"
#include "CharacterState.h"
#include <memory>
#include <stack>

class PacMan;

using namespace std;

typedef unique_ptr<State> statePtr; /**\typedef a unique pointer to the Game structure, to improve readability */

class Characters
{
public:
    /// Constructor
    Characters() {}

    /// Destructor
    ~Characters() {}

    /// Add a new state to the stack, which is set to become the current state.
    ///
    /// This state will become the new current state in the following cycle of the game loop. The user can specify whether the old state should be removed before adding the new state or keeping the it on the stack so as to return to it later

    void addState(std::shared_ptr<CharacterState> state);
    void checkCollisions(std::shared_ptr<PacMan> pacman_);

    /// Set the current state tobe removed

    /// Add or remove the current state according to the boolean flags set by addState() and removeState()
    void updateCharState();

    void removeCharState();

    bool isEmpty() const;
    std::shared_ptr<CharacterState> getTopState() const;
    void drawCharState();

    // New method to fetch the state based on type (e.g., EnemyChaseState)
    template <typename T>
    std::shared_ptr<T> getState()
    {
        for (const auto &state : char_states_)
        {
            // Dynamic cast to the desired type, such as EnemyChaseState
            auto desiredState = std::dynamic_pointer_cast<T>(state);
            if (desiredState)
            {
                return desiredState;
            }
        }
        return nullptr; // If no matching state is found
    }

    /// Get a pointer to the current state

    // statePtr& getCurrentState() {return states_.top();}

private:
    stack<statePtr> states_;

    std::shared_ptr<CharacterState> newState_;
    std::vector<std::shared_ptr<CharacterState>> char_states_; // Use vector instead of stack

    bool isAdding_;
    bool isRemoving_;
    bool isReplacing_;
};

#endif
