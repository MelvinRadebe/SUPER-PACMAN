#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

#include "Characters.h"
#include <raylib-cpp.hpp>

class CharacterState
{
public:
    /** \brief Default destructor */
    virtual ~CharacterState() {}

    /** Abstract function for state-specific update behavior */
    virtual void update() = 0; // Pure virtual update function for all ghosts

    /** Abstract function for state-specific drawing behavior */
    virtual void draw() = 0; // Pure virtual draw function for all ghosts

    /** Abstract function for state-specific entrance behavior */
    virtual void enter() = 0;

    /** Getters and setters for position */
    virtual raylib::Vector2 getPosition() const = 0;
    virtual void setPosition(const raylib::Vector2 &newPosition) = 0;
    virtual float getRadius() const = 0;
    

    /** Getters and setters for eaten state */


protected:
    raylib::Vector2 position_; // Store character position
    bool eaten_ = false;       // Track if character has been eaten
};

#endif
