#ifndef YOU_WON_STATE_H
#define YOU_WON_STATE_H

#include <raylib-cpp.hpp>
#include "State.h"
#include <memory>
#include <iostream>
#include <fstream>
#include "GameLoop.h"
#include "GameplayState.h"
#include "StateManager.h"
#include "SplashScreenState.h"
#include "ScoreManager.h"

class Game;

typedef std::shared_ptr<Game> gamePtr;

class YouWinScreenState : public State
{
public:
    YouWinScreenState(std::shared_ptr<ScoreManager> scoreManager);

    void initialise() override;
    void processInput() override;
    void draw() override;
    void update() override;

private:
    void writeNewScore();

    raylib::Texture2D background_;
    raylib::Font titleFont_;
    gamePtr game_;
    std::shared_ptr<ScoreManager> scoreManager_;
    float timeElapsed_;
};

#endif
