#include "YouWinScreenState.h"
#include <raylib-cpp.hpp>
#include <iostream>
#include <fstream>
#include "GameLoop.h"
#include <string>

YouWinScreenState::YouWinScreenState(std::shared_ptr<ScoreManager> scoreManager)
    : scoreManager_(scoreManager), timeElapsed_(0)
{
}

void YouWinScreenState::initialise()
{

    background_ = raylib::Texture2D(WONPATH);
}

void YouWinScreenState::processInput()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        // Restart the game or go back to splash screen
        GameLoop game{GAMEWIDTH, GAMEHEIGHT, GAMETITLE};
        game.run();
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        CloseWindow();
    }
}

void YouWinScreenState::draw()
{
    BeginDrawing();
    ClearBackground(raylib::Color::Black());

    // Draw background
    background_.Draw(0, 0, raylib::Color::White());

    // Draw Game Won message


    EndDrawing();
}

void YouWinScreenState::update()
{
    timeElapsed_ += GetFrameTime();
}

void YouWinScreenState::writeNewScore()
{
    std::ofstream file(SCORESPATH);
    if (file.is_open())
    {
        file << scoreManager_->GetScore(); // Write the new high score
        file.close();
    }
    else
    {
    }
}
