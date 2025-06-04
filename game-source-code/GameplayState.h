#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "State.h"
#include "PacMan.h"
#include "Inky.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Clyde.h"
#include "Maze.h"
#include "GameSettings.h"
#include "GameLoop.h"
#include <raylib-cpp.hpp>
#include <memory>
#include <vector>
#include <iostream>

class GameplayState : public State
{
public:
    GameplayState(float width, float height, gamePtr game);
    ~GameplayState()
    {
        UnloadTexture(blinkyTexture_); // Unload Blinky's texture when done
        UnloadTexture(inkyTexture_);
        UnloadTexture(clydeTexture_);
        UnloadTexture(pinkyTexture_);
    }

    void initialise() override;
    void processInput() override;
    void update() override;
    void draw() override;
    void PlayerEatsPowerPellet();
    std::shared_ptr<PacMan> getPacMan() { return pacman_; }
    Blinky getBlinky()
    {
        return blinky_;
    }
    Clyde getClyde()
    {
        return clyde_;
    }
    Inky getInky()
    {
        return inky_;
    }
    Pinky getPinky()
    {
        return pinky_;
    }

    void setMapName(const std::string &name)
    {
        mapName_ = name;
    }

    std::string mapName_ = "maze";

    // for testing

private:
    void InitializeGhosts();

    float screen_width_;
    float screen_height_;
    raylib::Texture2D background_;
    std::shared_ptr<Maze> maze_;
    std::shared_ptr<PacMan> pacman_;

    gamePtr game_ = make_shared<Game>();

    Inky inky_;
    Blinky blinky_;
    Clyde clyde_;
    Pinky pinky_;

    Texture2D blinkyTexture_;
    Texture2D inkyTexture_;
    Texture2D clydeTexture_;
    Texture2D pinkyTexture_;
};

#endif // GAMEPLAYSTATE_H
