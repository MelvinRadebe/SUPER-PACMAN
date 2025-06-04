#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "Characters.h"
#include <string>

#include "StateManager.h"

#include <raylib-cpp.hpp>
  enum class Direction
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
  };

// GameLoop.h
struct Game
{
  StateManager stateManager;
  Characters characters;
  Direction direction;
  Direction currentDirection_;


};

using gamePtr = std::shared_ptr<Game>; // Ensure this line is present
class GameLoop
{
public:
  GameLoop(float width, float height, const std::string &title);
  void run();

private:
  gamePtr game_ = make_shared<Game>();
  float screen_width_;
  float screen_height_;
  std::string title_;

  raylib::Window window_; // Make window a member of GameLoop
};

#endif // GAME_LOOP_H
