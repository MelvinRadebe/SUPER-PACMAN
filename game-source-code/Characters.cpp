#include "Characters.h"
#include <iostream>
#include "PacMan.h"

void Characters::addState(std::shared_ptr<CharacterState> state) {
    // Simply push the new state into the vector
    char_states_.push_back(std::move(state));  // Use move semantics for efficiency
    if (!char_states_.empty()) {
        char_states_.back()->enter();  // Initialize the new top state
    }
}






void Characters::removeCharState() {
    if (!char_states_.empty()) {
        char_states_.pop_back();  // Remove the last state
        if (!char_states_.empty()) {
            char_states_.back()->enter();  // Re-initialize the new top state
        }
    }
}

#include <iostream>
#include <memory>

void Characters::checkCollisions(std::shared_ptr<PacMan> pacman) {
    for (const auto &state : char_states_) {
        if (state) {
            auto enemyState = std::dynamic_pointer_cast<EnemyChaseState>(state);
            if (enemyState) {
                // Call CheckCollision with the appropriate parameters
                
                pacman->CheckCollision(enemyState->getPosition(), enemyState->getRadius(), *enemyState);
            }
        }
    }
}


void Characters::updateCharState() {
    // Update each character state independently
    for (const auto &state : char_states_) {
        if (state) {
            state->update();  // Update each character state
            
        }
    }
}

void Characters::drawCharState() {
    // Draw each character state independently
    for (const auto &state : char_states_) {
        if (state) {
            state->draw();  // Draw each character state
        }
    }
}
