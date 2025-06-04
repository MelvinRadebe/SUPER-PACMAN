#include "SplashScreenState.h"

SplashScreenState::SplashScreenState(float width, float height, gamePtr game)
    : screen_width_{width}, screen_height_{height}, game_{game}, timeElapsed_{0}, splashScreen_{true} {}

void SplashScreenState::initialise() {
    try {
        background_ = raylib::Texture2D(SPLASHBACKPATH);
     
    } catch (...) {
        std::cerr << "Failed to load splash backgrounds." << std::endl;
    }

    try {
        titleFont_ = raylib::Font(FONTPATH);
    } catch (...) {
        std::cerr << "Failed to load title font." << std::endl;
    }
}

void SplashScreenState::processInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        game_->stateManager.addState(std::make_unique<GameplayState>(screen_width_, screen_height_, game_));
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();
    }
}

void SplashScreenState::draw() {
    BeginDrawing();
    ClearBackground(raylib::Color::Black());

    // Draw backgrounds
    background_.Draw(0, 0, raylib::Color::White());
  


    
    // Flashing "Press SPACE to start" text
    if (timeElapsed_ > 0.1) {
        timeElapsed_ = 0; // Reset timer
        raylib::DrawText("PUSH ENTER KEY TO START", screen_width_ / 2 - 230, screen_height_ / 2 + 40, 30, raylib::Color::White());
    } else {
        raylib::DrawText("PUSH ENTER KEY TO START", screen_width_ / 2 -230, screen_height_ / 2 + 40, 30, raylib::Color::SkyBlue());
    }

    EndDrawing();
}

void SplashScreenState::update() {
    timeElapsed_ += GetFrameTime();
}

bool SplashScreenState::isSplashScreenOver() const {
    return !splashScreen_;
}
