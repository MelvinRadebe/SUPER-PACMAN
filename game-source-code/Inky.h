#ifndef INKY_H
#define INKY_H

#include "Characters.h"
#include "EnemyChaseState.h"
#include "Maze.h"
#include "PacMan.h"
#include <raylib-cpp.hpp>
#include <memory>
#include <stack>

struct Game;

class Inky : public EnemyChaseState
{
public:
    using charStatePtr = std::shared_ptr<CharacterState>;
    typedef shared_ptr<Game> gamePtr;

    // Constructor with initializer list
    Inky(float x, float y, float speed, float radius, std::shared_ptr<Maze> maze, raylib::Color color, std::shared_ptr<PacMan> pacman, gamePtr game, Texture2D inkyTexture);
    Inky();
    // Default constructor

    // ~Inky()
    // {
    //     UnloadTexture(inkyTexture_);
    // }

    std::string getName()
    {
        return "Blinky";
    }

    void update();

    void draw()
    {
        std::cout << x_ << "  " << y_ << endl;

        // Check if the power pellet is eaten
    }

    raylib::Vector2 getPosition()
    {
        auto State = game_->characters.getState<EnemyChaseState>();

        if (State)
        {
            
            Vector2 currentPos = State->getPosition();
            return currentPos;
        }
        return {x_, y_};
    }
    void setEaten(bool value) { eaten_ = value; }
    bool isEaten() const { return eaten_; }
    void setPosition(const raylib::Vector2 &newPosition)
    {

        
        x_ = newPosition.x;
        y_ = newPosition.y;
    }

    void ResetPosition()
    {
        x_ = startingX_;
        y_ = startingY_;
    }

    float getRadius() const
    {
        return radius_;
    }
     void set() 
    {
        
        
    }

private:
    float x_;
    float y_;
    float speed_;
    float radius_;
    std::shared_ptr<Maze> maze_;
    std::shared_ptr<PacMan> pacman_;
    bool eaten_ = false;
    raylib::Color color_;
    float startingX_;
    float startingY_;

    Texture2D inkyTexture_;


    gamePtr game_ = make_shared<Game>();
};

#endif // INKY_H
