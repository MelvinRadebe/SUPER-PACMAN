#include "Inky.h"
#include "EnemyChaseState.h"
#include "Characters.h"
#include <iostream>

Inky::Inky(float x, float y, float speed, float radius, std::shared_ptr<Maze> maze, raylib::Color color, std::shared_ptr<PacMan> pacman, gamePtr game, Texture2D inkyTexture)
    : x_(x), y_(y), speed_(speed), radius_(radius), maze_(maze), pacman_(pacman), color_(color), game_(game), inkyTexture_(inkyTexture)
{
    startingX_ = x_;
    startingY_ = y_;

    // Add an initial state to the character state manager (Characters class)
    auto initialState = std::make_shared<EnemyChaseState>(x_, y_, speed_, radius_, maze_, color_, pacman_, inkyTexture_);
    game_->characters.addState(initialState); // Add the state to the state manager
}

Inky::Inky() {}

// Update method
void Inky::update()
{
  

    // Update character states through the Characters class
}

// Example of other methods (draw, getPosition, setPosition, etc.)
