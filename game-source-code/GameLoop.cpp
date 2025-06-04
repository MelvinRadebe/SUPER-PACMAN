#include "GameSettings.h"
#include "SplashScreenState.h"

#include <raylib-cpp.hpp>
#include <iostream>
#include "GameLoop.h"

GameLoop::GameLoop(float width, float height, const std::string &title)
    : screen_width_{width}, screen_height_{height}, title_{title}
{
}
void GameLoop::run()
{
    raylib::Window window(screen_width_, screen_height_, title_);
    window.SetTargetFPS(60);

    // //std::cout << "Before adding state" << std::endl;

    try
    {
        
        // auto splashState = std::make_unique<SplashScreenState>(screen_width_,screen_height_,game_);

        game_->stateManager.addState(make_unique<SplashScreenState>(screen_width_, screen_height_, game_));

     
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception during state management: " << e.what() << std::endl;
    }

    while (!window.ShouldClose())
    {
        game_->stateManager.processStateChanges(); // Handle state transitions

        if (game_->stateManager.getCurrentState())
        {

            game_->stateManager.getCurrentState()->processInput();
            game_->stateManager.getCurrentState()->update();
            game_->stateManager.getCurrentState()->draw();
        }
    }

  
}
