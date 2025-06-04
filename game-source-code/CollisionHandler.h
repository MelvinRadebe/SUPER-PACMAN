#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Maze.h"
#include <raylib-cpp.hpp>

class CollisionHandler {
public:
    static bool handleCollisions(const raylib::Vector2& newPosition, const raylib::Vector2& currentTile, 
                                 const raylib::Vector2& newTile, float speed, 
                                 const raylib::Rectangle* playerRect, const Maze* maze);
};

#endif // COLLISIONHANDLER_H
