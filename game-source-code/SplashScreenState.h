#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include <raylib-cpp.hpp>
#include "State.h"
#include <memory>
#include <iostream>
#include "GameLoop.h"
#include "GameplayState.h"
#include "StateManager.h"

typedef std::shared_ptr<Game> gamePtr;

class SplashScreenState : public State {
public:
    SplashScreenState(float width, float height, gamePtr game);

    void initialise() override;
    void processInput() override;
    void draw() override;
    void update() override;
    bool isSplashScreenOver() const;

private:
    float screen_width_;
    float screen_height_;
    bool splashScreen_;
    float timeElapsed_; // For flashing text effect
    raylib::Texture2D background_;
    raylib::Texture2D background2_;
    raylib::Font titleFont_;
     gamePtr game_ = make_shared<Game>();
};

#endif // SPLASH_STATE_H
