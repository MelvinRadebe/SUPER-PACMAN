#include "YouLostScreenState.h"
#include "raylib-cpp.hpp"
#include "GameLoop.h"
#include <iostream>
#include <fstream>

YouLostScreenState::YouLostScreenState(std::shared_ptr<ScoreManager> scoreManager)
    : scoreManager_(scoreManager) {}

void YouLostScreenState::initialise()
{

    background_ = raylib::Texture2D(LOSTPATH);

    titleFont_ = raylib::Font(FONTPATH);
}

void YouLostScreenState::processInput()
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

void YouLostScreenState::draw()
{
    BeginDrawing();
    ClearBackground(raylib::Color::Black());

    // Draw background scaled to game window size
    ::DrawTexturePro(background_,
                     raylib::Rectangle{0, 0, static_cast<float>(background_.width), static_cast<float>(background_.height)},
                     raylib::Rectangle{0, 0, static_cast<float>(GAMEWIDTH), static_cast<float>(GAMEHEIGHT)},
                     raylib::Vector2{0, 0}, 0.0f, raylib::Color::White());

    writeNewScore();

    EndDrawing();
}

void YouLostScreenState::update()
{
}

void YouLostScreenState::writeNewScore()
{
    // Write the new high score to the file
    std::ofstream file(SCORESPATH);
    if (file.is_open())
    {
        file << scoreManager_->GetScore(); // Write the new high score
        file.close();

    
    }
}
