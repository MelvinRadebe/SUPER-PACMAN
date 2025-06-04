#ifndef GHOST_H
#define GHOST_H

#include <memory>
#include <raylib-cpp.hpp>

//to be used for inheritance soon


class Ghost   {
public:
    virtual ~Ghost() = default;

    virtual void update() = 0;  // Pure virtual update function for all ghosts

    // Getters and setters
    virtual raylib::Vector2 getPosition() const = 0;
    virtual void setPosition(const raylib::Vector2 &newPosition) = 0;
    virtual bool IsEaten() const = 0;
    virtual void setEaten(bool value) = 0;
     virtual void draw() const = 0; // Pure virtual draw function for all ghosts

protected:
  
};

#endif // GHOST_H
