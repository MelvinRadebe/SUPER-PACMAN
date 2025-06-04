#include "CollisionHandler.h"

// Handle collision logic
bool CollisionHandler::handleCollisions(const raylib::Vector2& newPosition, const raylib::Vector2& currentTile, 
                                         const raylib::Vector2& newTile, float speed, 
                                         const raylib::Rectangle* playerRect, const Maze* maze) 
{
    // Define tile size based on the maze
    float tileLength = maze->GetTileWidth();
    
    // Get tile coordinates
    int currentTileX = static_cast<int>(currentTile.x / tileLength);
    int currentTileY = static_cast<int>(currentTile.y / tileLength);
    int newTileX = static_cast<int>(newTile.x / tileLength);
    int newTileY = static_cast<int>(newTile.y / tileLength);
    
    // Check if the new tile is a wall or invalid tile
    if (maze->GetTile(newTileX, newTileY).type == 'W') {
        return false; // Collision with wall
    }
    
    // If there is a playerRect provided, check collision with it
    if (playerRect) {
        // Check collision with other entities
        Rectangle playerRectRect = {playerRect->x - playerRect->width / 2,
                                    playerRect->y - playerRect->height / 2,
                                    playerRect->width,
                                    playerRect->height};

        if (CheckCollisionRecs(playerRectRect, {newPosition.x - 10, newPosition.y - 10, 20, 20})) {
            return false; // Collision with another entity
        }
    }
    
    // Additional maze boundary check if needed
    if (newTileX < 0 || newTileY < 0 || newTileX >= maze->GetWidth() || newTileY >= maze->GetHeight()) {
        return false; // Out of maze boundaries
    }
    
    return true; // No collision
}
