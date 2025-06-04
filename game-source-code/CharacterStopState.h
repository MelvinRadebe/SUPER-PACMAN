#ifndef CHARACTER_STOP_STATE_H
#define CHARACTER_STOP_STATE_H

/** \file CharacterStop.h
    \brief Contains the class definition for an abstract "CharacterStopState" class, which will be inherited by
    character states which do not move
*/
#include "Character.h"
#include "CharacterState.h"

#include "Maze.h"
#include "Player.h"
#include "Enemy.h"

/** \class CharacterStopState
 *  \brief Base class for stationary character states in Harambe's Quest
 *
 *  This class is a base class which will be inherited by multiple
 *  character states. It is a purely abstract class which has no members
 *  or implementation of its own, but the interface is inherited by its
 *  derived classes.
 */

class CharacterStopState: public CharacterState
{
    public:
        typedef Player* playerPtr; /**< \typedef for a pointer to a Player, to improve readability */
        typedef Maze* mazePtr;  /**< \typedef for a pointer to a Maze, to improve readability */
        typedef Enemy* enemyPtr; /**< \typedef for a pointer to an Enemy, to improve readability */

        /** \brief Default constructor */
        CharacterStopState() {}
        /** \brief Default destructor */
        virtual ~CharacterStopState() {}

        /** Abstract function for state specific update behaviour*/
        virtual void update() = 0;

        /** Abstract function for state specific entrance behaviour*/
        virtual void enter() = 0;

    protected:

    private:
};

#endif
