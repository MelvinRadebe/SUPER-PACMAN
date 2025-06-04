#include "PacMan.h"
#include "Maze.h"
#include "GameSettings.h"
#include <iostream>
#include "YouWinScreenState.h"
#include "YouLostScreenState.h"
#include "Inky.h"

PacMan::PacMan(float x, float y, float radius, float speed, std::shared_ptr<Maze> maze, gamePtr game)
    : x_(x), y_(y), radius_(radius), speed_(speed), maze_(maze), foodCount_(31),
      game_(game), ghostEaten_(false), scoreManager_(std::make_shared<ScoreManager>(GAMEWIDTH, GAMEHEIGHT)), PowerPelletTime_(0),
      powerPelletEaten_(false), timeElapsed_(0), currentTime_(0) {}

void PacMan::ProcessInput()
{
    // Handle movement input (arrow keys) and set the direction
    if (IsKeyDown(KEY_UP))
    {
        direction_ = Direction::UP;
        rotation = 270.0f;   // Pac-Man faces up
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        direction_ = Direction::DOWN;
        rotation = 90.0f;  // Pac-Man faces down
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        direction_ = Direction::LEFT;
        rotation = 180.0f;  // Pac-Man faces left
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        direction_ = Direction::RIGHT;
        rotation = 0.0f;    // Pac-Man faces right
    }
}


void PacMan::moveNormalSpeed()
{
    // Calculate new position based on direction
    float newX = x_;
    float newY = y_;

    switch (direction_)
    {
    case Direction::UP:
        newY -= speed_;

        if (CanMoveUp(newX, newY))
        {

            y_ = newY;
        }
        break;
    case Direction::DOWN:
        newY += speed_;
        if (CanMoveDown(newX, newY))
        {
            y_ = newY;
        }
        break;
    case Direction::LEFT:
        newX -= speed_;
        if (CanMoveLeft(newX, newY))
        {
            x_ = newX;
        }
        break;
    case Direction::RIGHT:

        newX += speed_;
     
        if (CanMoveRight(newX, newY))
        {

            x_ = newX;
        }
        break;
    default:
        break;
    }
}

void PacMan::Update()
{
    
    
    // Move Pac-Man according to the current direction
    moveNormalSpeed();

    // Check if Pac-Man collects a key after moving

    PlayerCollectsKey();
    PlayerCollectsFruit();
    PlayerEatsPowerPellet();
    if (isPowerPelletEaten())
    {
        timeElapsed_ += GetFrameTime();

   

        if (timeElapsed_ > 5)
        {
            timeElapsed_ = 0;
            setPowerPelletMode(false);
            // check in gameplay state.  PlayerEatsPowerPellet();
        }
    }
}


void PacMan::Draw()
{
    // Example: Initial direction (0 degrees means facing right)
    if (rotation == 0.0f) {
        rotation = 0.0f;  // Ensure it's initialized
    }

    // Existing code for animating the mouth
    scoreManager_->DrawScore();

    if (isPowerPelletEaten()) {
        currentRadius_ = radius_ * 2;
    } else {
        currentRadius_ = radius_;
    }

    static float mouthAngle = 0.0f;
    static bool mouthOpening = true;
    float mouthSpeed = 180.0f * GetFrameTime();

    if (mouthOpening) {
        mouthAngle += mouthSpeed;
        if (mouthAngle >= 45.0f) {
            mouthAngle = 45.0f;
            mouthOpening = false;
        }
    } else {
        mouthAngle -= mouthSpeed;
        if (mouthAngle <= 5.0f) {
            mouthAngle = 5.0f;
            mouthOpening = true;
        }
    }

    float startAngle = 0.0f;
    float endAngle = 360.0f;

    switch ((int)rotation) {  // Assuming rotation is in degrees (0, 90, 180, 270)
        case 0:    // Facing right
            startAngle = mouthAngle;
            endAngle = 360.0f - mouthAngle;
            break;
        case 90:   // Facing up
            startAngle = 90.0f + mouthAngle;
            endAngle = 450.0f - mouthAngle;
            break;
        case 180:  // Facing left
            startAngle = 180.0f + mouthAngle;
            endAngle = 540.0f - mouthAngle;
            break;
        case 270:  // Facing down
            startAngle = 270.0f + mouthAngle;
            endAngle = 630.0f - mouthAngle;
            break;
        default:
            break;
    }

    DrawCircleSector(raylib::Vector2(x_, y_), currentRadius_, startAngle, endAngle, 100, YELLOW);

    switch ((int)rotation) {
        case 0:    // Eye for facing right
            DrawCircle(x_ + currentRadius_ / 3, y_ - currentRadius_ / 3, currentRadius_ / 10, BLACK);
            break;
        case 90:   // Eye for facing up
            DrawCircle(x_ + currentRadius_ / 3, y_ - currentRadius_ / 3, currentRadius_ / 10, BLACK);
            break;
        case 180:  // Eye for facing left
            DrawCircle(x_ - currentRadius_ / 3, y_ - currentRadius_ / 3, currentRadius_ / 10, BLACK);
            break;
        case 270:  // Eye for facing down
            DrawCircle(x_ + currentRadius_ / 3, y_ + currentRadius_ / 3, currentRadius_ / 10, BLACK);
            break;
        default:
            break;
    }
}





raylib::Vector2 PacMan::getPosition() const
{
    // Return Pac-Man's position as a Vector2
    return raylib::Vector2(x_, y_);
}

void PacMan::CheckCollision(const raylib::Vector2 &ghostPosition, float ghostRadius, EnemyChaseState &enemy)
{
    // Check if the distance between Pac-Man and the ghost is less than the sum of their radii
    if (!isPowerPelletEaten())
    {
        if (CheckCollisionCircles(raylib::Vector2(x_, y_), radius_, ghostPosition, ghostRadius))
        {
            game_->stateManager.addState(make_unique<YouLostScreenState>(scoreManager_));
        }
    }
    else
    {
        if (CheckCollisionCircles(raylib::Vector2(x_, y_), radius_, ghostPosition, ghostRadius))
        {
            if (!enemy.isEaten())
            {                         // Only eat the ghost if it hasn't been eaten yet
                enemy.setEaten(true); // Mark the ghost as eaten
                // GhostEaten();  // Pac-Man eats the ghost
            }
        }
    }
}



bool PacMan::CanMove(float newX, float newY) const
{
  

    // Convert newX and newY to tile coordinates based on the maze's tile size
    float tileWidth = static_cast<float>(maze_->GetTileWidth());
    float tileHeight = static_cast<float>(maze_->GetTileHeight());

    int tileX = static_cast<int>(newX / tileWidth);
    int tileY = static_cast<int>(newY / tileHeight);

  
    return maze_->IsEmptySpace(tileX, tileY);
}

void PacMan::PlayerCollectsKey()
{
    // Convert Pac-Man's current position to tile coordinates
    float tileWidth = static_cast<float>(maze_->GetTileWidth());
    float tileHeight = static_cast<float>(maze_->GetTileHeight());

    int tileX = static_cast<int>(x_ / tileWidth);
    int tileY = static_cast<int>(y_ / tileHeight);

    // Check if the current tile is a key ('K')
    if (maze_->GetTileType(tileX, tileY) == 'K')
    {
     
        // Open gates corresponding to the key's position
        maze_->OpenGateForKey(tileX, tileY);

        // Remove the key from the maze (set the tile to empty space 'E')
        maze_->SetTile(tileX, tileY, 'E');
    }
}

void PacMan::PlayerCollectsFruit()
{
    // Convert Pac-Man's current position to tile coordinates
    float tileWidth = static_cast<float>(maze_->GetTileWidth());
    float tileHeight = static_cast<float>(maze_->GetTileHeight());
    //converting pacman's pixel coordinates to maze grid coordiantes.

    int tileX = static_cast<int>(x_ / tileWidth);
    int tileY = static_cast<int>(y_ / tileHeight);

    // Check if the current tile is a key ('K')
    if (maze_->GetTileType(tileX, tileY) == 'F')
    {
      
        scoreManager_->UpdateScore();
     
        foodCount_--;
        if (foodCount_ == 0)
        {
            game_->stateManager.addState(make_unique<YouWinScreenState>(scoreManager_));
        }
   
        // Remove the key from the maze (set the tile to empty space 'E')
        maze_->SetTile(tileX, tileY, 'E');
    }
}
void PacMan::PlayerEatsPowerPellet()
{

 
    float tileWidth = static_cast<float>(maze_->GetTileWidth());
    float tileHeight = static_cast<float>(maze_->GetTileHeight());

    int tileX = static_cast<int>(x_ / tileWidth);
    int tileY = static_cast<int>(y_ / tileHeight);

  
    if (maze_->GetTileType(tileX, tileY) == 'P')
    {
      
        PowerPelletEaten();
    
        // Remove the key from the maze (set the tile to empty space 'E')
        maze_->SetTile(tileX, tileY, 'E');
    }
}
