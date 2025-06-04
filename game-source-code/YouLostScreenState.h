#ifndef YOULOSTSTATE_H
#define YOULOSTSTATE_H

#include <raylib-cpp.hpp>
#include <memory>
#include <iostream>
#include <fstream>
#include "State.h"
#include "ScoreManager.h"

// Forward declaration of Game class
struct Game;

typedef std::shared_ptr<Game> gamePtr;

class YouLostScreenState : public State
{
public:
    // Constructor
    YouLostScreenState(std::shared_ptr<ScoreManager> scoreManager);

    // Overriding methods from State interface
    void initialise() override;
    void processInput() override;
    void draw() override;
    void update() override;

private:
    // Helper method to write the new high score to a file
    void writeNewScore();

    // Member variables
    float screen_width_;
    float screen_height_;
    raylib::Texture2D background_;
    raylib::Font titleFont_;
    gamePtr game_ = std::make_shared<Game>();
    std::shared_ptr<ScoreManager> scoreManager_;

};

#endif // YOULOSTSTATE_H
