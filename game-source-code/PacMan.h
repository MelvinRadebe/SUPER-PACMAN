#ifndef PACMAN_H
#define PACMAN_H

#include "Maze.h"
#include "Inky.h"
#include "ScoreManager.h"
#include <raylib-cpp.hpp>
#include <memory>
#include <vector>
#include "GameLoop.h"
#include "EnemyChaseState.h"

class EnemyChaseState;

class YouLostScreenState;
struct Game;
// Forward declaration of Maze class
class Maze;

// Enum class for movement direction
typedef std::shared_ptr<Game> gamePtr;


class PacMan
{
public:
    PacMan(float x, float y, float radius, float speed, std::shared_ptr<Maze> maze, gamePtr game);

    void SetPosition(float x, float y) { x_ = x; y_ = y; }

    void SetDirection(Direction direction) { direction_ = direction; }

    void ProcessInput();                  // Input handling method
    void Update();                       // Movement update method
    void Draw() ;                   // Draw method
    raylib::Vector2 getPosition() const; // Getter for Pac-Man's position

    void CheckCollision(const raylib::Vector2 &ghostPosition, float ghostRadius, EnemyChaseState &Enemy) ;
    bool CanMoveUp(float newX, float newY) const
    {
        return CanMove(newX, newY - radius_);
    }

    bool CanMoveDown(float newX, float newY) const
    {
        return CanMove(newX, newY + radius_);
    }

    bool CanMoveLeft(float newX, float newY) const
    {
        return CanMove(newX - radius_, newY);
    }

    bool CanMoveRight(float newX, float newY) 
    {
      
        return CanMove(newX + radius_, newY);
    }
    void PlayerCollectsKey();
    void PlayerCollectsFruit();
    void PlayerEatsPowerPellet();

    void PowerPelletEaten()
    {
       
        powerPelletEaten_ = true;
    }
    void setPowerPelletMode(bool state)
    {
        powerPelletEaten_ = state;

    }
    void GhostEaten() { ghostEaten_ = true; } 
    bool isPowerPelletEaten() { return powerPelletEaten_; }
    bool isGhostEaten() const { return ghostEaten_; }

private:
    float x_, y_;
    float radius_,currentRadius_;
    float speed_;
    std::shared_ptr<Maze> maze_;
    Direction direction_ = Direction::NONE;
    int foodCount_;
    std::shared_ptr<ScoreManager> scoreManager_;
    float timeElapsed_, currentTime_;
    float PowerPelletTime_;

    void moveNormalSpeed();
    bool CanMove(float newX, float newY) const;
    gamePtr game_ = std::make_shared<Game>();
    bool ghostEaten_;
    // std::vector<Ghost> ghosts_;
    bool powerPelletEaten_;
    Direction futureDirection_;  // Store future direction
    float rotation;


 
};

#endif // PACMAN_H
