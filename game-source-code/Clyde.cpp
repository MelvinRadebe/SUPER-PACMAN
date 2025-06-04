#include "Clyde.h"
#include "EnemyChaseState.h"
#include "Characters.h"
#include <iostream>

Clyde::Clyde(float x, float y, float speed, float radius, std::shared_ptr<Maze> maze, raylib::Color color, std::shared_ptr<PacMan> pacman, gamePtr game,Texture2D clydeTexture)
    : x_(x), y_(y), speed_(speed), radius_(radius), maze_(maze), pacman_(pacman), color_(color), game_(game),clydeTexture_(clydeTexture)
{
    startingX_ = x_;
    startingY_ = y_;

    // Add an initial state to the character state manager (Characters class)
    auto initialState = std::make_shared<EnemyChaseState>(x_, y_, speed_, radius_, maze_, color_, pacman_,clydeTexture_);
    game_->characters.addState(initialState);  // Add the state to the state clydeTexture_
}

Clyde::Clyde() {}

// Update method
void Clyde::update() {
    // Update the character states through the Characters class
    // game_->characters.updateCharState();

    // // If there is an active state, update Blinky's position
    // if (!game_->characters.isEmpty()) {
    //     // Assuming getTopState() returns the top character state
    //     auto currentState = game_->characters.getTopState();

    //     if (currentState) {
    //         // Update the state and get the new position for Blinky
    //         currentState->update();
    //         auto newPos = currentState->getPosition();
    //         x_ = newPos.x;
    //         y_ = newPos.y;
    //     }
    // } else {
    //     std::cerr << "Warning: No active states for Blinky!" << std::endl;
    // }
}

// Example of other methods (draw, getPosition, setPosition, etc.)

