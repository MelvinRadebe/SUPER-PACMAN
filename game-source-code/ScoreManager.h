#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <raylib-cpp.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "GameSettings.h"

class ScoreManager
{
public:
    // Constructor to initialize screen width, height, and load the high score from file
    ScoreManager(float width, float height);
    

    // Method to update the score
    void UpdateScore();

    // Method to draw the score and high score on the screen
    void DrawScore() const;

    // Getter for the current score
    int GetScore() const;

    // Getter for the high score
    int GetHighScore() const;

private:
    // Private member variables
    float screen_width_;
    float screen_height_;
    int score_;
    int highScore_;

    // Method to load the high score from a file
    void LoadHighScore();
};

#endif // SCORE_MANAGER_H
