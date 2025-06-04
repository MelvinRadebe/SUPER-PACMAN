#include "ScoreManager.h"

// Constructor definition
ScoreManager::ScoreManager(float width, float height)
    : score_(0), highScore_(0), screen_width_(width), screen_height_(height)
{
    // Load high score from the file
    LoadHighScore();
}

// Method to update the score by adding 200 points
void ScoreManager::UpdateScore()
{
    score_ += FRUITSCORE;
}




// Method to draw the current score and high score on the screen
void ScoreManager::DrawScore() const
{
    std::string scoreText = "Score: " + std::to_string(score_);
    raylib::DrawText(scoreText, 400, 0, 35, raylib::Color::White());

}

// Getter for the current score
int ScoreManager::GetScore() const
{
    return score_;
}

// Getter for the high score
int ScoreManager::GetHighScore() const
{
    return highScore_;
}

// Method to load the high score from a file
void ScoreManager::LoadHighScore()
{
    std::ifstream file(SCORESPATH);
    if (file.is_open())
    {
        file >> highScore_;
        file.close();
    }
    else
    {
        
    }
}
