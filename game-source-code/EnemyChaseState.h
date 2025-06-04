#ifndef ENEMY_CHASE_STATE_H
#define ENEMY_CHASE_STATE_H

#include "CharacterState.h"
#include <chrono>
#include <utility> // For std::pair
#include <raylib-cpp.hpp>
#include <queue>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm> // For std::reverse

class PacMan;
class Maze;

struct Node
{
    int x, y;
    float gCost, hCost, fCost;
    Node *parent;

    bool operator>(const Node &other) const
    {
        return fCost > other.fCost;
    }
};

class EnemyChaseState : public CharacterState
{
public:
    // Constructor
    EnemyChaseState(float x, float y, float speed, float radius, std::shared_ptr<Maze> maze, raylib::Color color, std::shared_ptr<PacMan> pacman,Texture2D enemyTexture);
    EnemyChaseState() {}

      ~EnemyChaseState()
    {
        UnloadTexture(enemyTexture_);
    }

    void draw() override
    {
        Draw();
    }

    // Implement abstract functions from CharacterState
    void update() override; // Update the ghost's behavior
    void enter() override;
    // Custom functions for Inky
    void Update(float pacmanX, float pacmanY);
    bool IsTowardsPacman(int startX, int startY, int targetX, int targetY, float pacmanX, float pacmanY);

    // Draw the ghost
    void Draw();
    raylib::Vector2 getPosition() const override
    {
        return {x_, y_}; // Return the stored position
    }

    void setPosition(const raylib::Vector2 &newPosition) override
    {
        position_ = newPosition; // Set the new position
    }

    bool isEaten() const
    {

        return eaten_; // Return the eaten status
    }

    void setEaten(bool value)
    { 

        eaten_ = value; // Set the eaten status
    }
    // Getters and setters
    // raylib::Vector2 getPosition() const;
    float getRadius() const override
    {
        return radius_;
    }
    // void setPosition(const raylib::Vector2 &newPosition);
//BFS
    std::vector<Node> FindPathBFS(int startX, int startY, int targetX, int targetY);

    // Basic movement update towards Pac-Man
    void BasicMovement(float pacmanX, float pacmanY);

    // Check if the ghost can move to the new position
    bool CanMove(float newX, float newY) const;

    // Check if the ghost has been in the same position for the required time
    bool HasBeenInSamePositionFor(float duration) const;

private:
    float x_;                    // Current x position of the ghost
    float y_;                    // Current y position of the ghost
    float speed_, currentSpeed_; // Speed of the ghost
    float radius_;               // Radius for detection or influence
    std::shared_ptr<Maze> maze_;               // Reference to the Maze object
    float timeElapsed_;
    std::shared_ptr<PacMan> pacman_;
    float spawnX_;
    float spawnY_;

    // For tracking if the ghost is stuck
    float lastX_;                                         // Last x position of the ghost
    float lastY_;                                         // Last y position of the ghost
    std::chrono::steady_clock::time_point stuckStartTime; // Timestamp when the ghost was first detected as stuck
    int stuckDuration;                                    // Duration for which the ghost has been stuck
    bool escapeMode;                                      // Flag to determine if the ghost is in escape mode
    std::chrono::steady_clock::time_point escapeEndTime;
    raylib::Color color_; // New color attribute
    bool eaten_;          // Track whether the ghost has been eaten
    Texture2D enemyTexture_;
    Texture2D scaredGhost_;
    Texture2D ghostEaten_;
};

#endif