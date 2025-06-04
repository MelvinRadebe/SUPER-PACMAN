#include "Inky.h"
#include "Blinky.h"
#include <queue>
#include <vector>
#include <cmath> // For abs
#include <iostream>
#include "Maze.h"
#include "PacMan.h"


float heuristic(int x1, int y1, int x2, int y2)
{
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

// Get neighboring nodes
std::vector<Node> GetNeighbors(const Node &currentNode, const Maze &maze)
{
    std::vector<Node> neighbors;

    // Possible movements (up, down, left, right)
    std::vector<std::pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    for (const auto &[dx, dy] : directions)
    {
        int newX = currentNode.x + dx;
        int newY = currentNode.y + dy;

        if (maze.IsEmptySpace(newX, newY))
        {
            neighbors.push_back({newX, newY, 0, 0, 0, nullptr}); // Valid neighbor
        }
    }

    return neighbors;
}

EnemyChaseState::EnemyChaseState(float x, float y, float speed, float radius, std::shared_ptr<Maze> maze, raylib::Color color, std::shared_ptr<PacMan> pacman, Texture2D enemyTexture)
    : x_(x), y_(y), speed_(speed), radius_(radius), maze_(maze), color_(color), pacman_(pacman), enemyTexture_(enemyTexture), eaten_(false)
{
    if (!maze_)
    {
        std::cerr << "Maze pointer is null!" << std::endl;
    }
    if (!pacman_)
    {
        std::cerr << "PacMan pointer is null!" << std::endl;
    }

    Image scaredImage = LoadImage("../resources/sprites/scaredGhost.png"); // Replace with the actual path to the texture image
    ImageResize(&scaredImage, 36, 36);                                      // Resize the image to 36x36
    scaredGhost_ = LoadTextureFromImage(scaredImage);                       // Create the texture from the resized image

    Image GhostEatenImage = LoadImage("../resources/sprites/ghostEaten.png"); // Replace with the actual path to the texture image
    ImageResize(&GhostEatenImage, 36, 36);                                     // Resize the image to 36x36
    ghostEaten_ = LoadTextureFromImage(GhostEatenImage);
}

void EnemyChaseState::update()
{
    if (!maze_ || !pacman_)
    {
        std::cerr << "Null pointer in update method!" << std::endl;
        return;
    }

    // Additional debug output

    // Check if pacman_ is valid before calling its method
    if (pacman_)
    {
        Vector2 pacmanPosition = pacman_->getPosition();
        Update(pacmanPosition.x, pacmanPosition.y);
    }
    else
    {
    }
}

void EnemyChaseState::enter()

{
}

std::vector<Node> EnemyChaseState::FindPathBFS(int startX, int startY, int targetX, int targetY)
{
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
    std::vector<std::vector<bool>> closedList(maze_->GetHeight(), std::vector<bool>(maze_->GetWidth(), false));

    Node startNode{startX, startY, 0, heuristic(startX, startY, targetX, targetY), 0, nullptr};
    openList.push(startNode);

    while (!openList.empty())
    {
        Node currentNode = openList.top();
        openList.pop();

        if (currentNode.x == targetX && currentNode.y == targetY)
        {
            std::vector<Node> path;
            Node *pathNode = &currentNode;

            while (pathNode != nullptr)
            {
                path.push_back(*pathNode);
                pathNode = pathNode->parent;
            }
            return path;
        }

        closedList[currentNode.y][currentNode.x] = true;

        auto neighbors = GetNeighbors(currentNode, *maze_);
        for (auto &neighbor : neighbors)
        {
            if (closedList[neighbor.y][neighbor.x])
            {
                continue;
            }

            float tentativeGCost = currentNode.gCost + 1.0f;
            neighbor.gCost = tentativeGCost;
            neighbor.hCost = heuristic(neighbor.x, neighbor.y, targetX, targetY);
            neighbor.fCost = neighbor.gCost + neighbor.hCost;
            neighbor.parent = new Node(currentNode);

            openList.push(neighbor);
        }
    }

    return {};
}

void EnemyChaseState::Update(float pacmanX, float pacmanY)

{
    if (!maze_)
    {
        std::cerr << "Maze pointer is null in Update!" << std::endl;
        return;
    }

    spawnX_ = static_cast<int>(12 * 32 / maze_->GetTileWidth());
    spawnY_ = static_cast<int>(10 * 32 / maze_->GetTileHeight());
    int startX = static_cast<int>(x_ / maze_->GetTileWidth());
    int startY = static_cast<int>(y_ / maze_->GetTileHeight());
    timeElapsed_ += GetFrameTime();

    int targetX, targetY;

    if (pacman_->isPowerPelletEaten())
    {
        if (isEaten())
        {
            // Move to ghost house
            currentSpeed_ = 10;
            targetX = spawnX_;
            targetY = spawnY_;
        }
        else
        {
            // Calculate vector pointing away from Pac-Man
            float directionX = startX - static_cast<int>(pacmanX / maze_->GetTileWidth());
            float directionY = startY - static_cast<int>(pacmanY / maze_->GetTileHeight());

            // Normalize the direction vector
            float distance = std::sqrt(directionX * directionX + directionY * directionY);

            // Calculate target position moving away from Pac-Man
            targetX = startX + static_cast<int>(directionX * 4);
            targetY = startY + static_cast<int>(directionY * 4);

            // Ensure the target is a valid empty space
            if (!maze_->IsEmptySpace(targetX, targetY) || IsTowardsPacman(startX, startY, targetX, targetY, pacmanX, pacmanY))
            {
                // Fallback to a valid nearby position
                auto neighbors = GetNeighbors({startX, startY, 0, 0, 0, nullptr}, *maze_);
                for (const auto &neighbor : neighbors)
                {
                    if (maze_->IsEmptySpace(neighbor.x, neighbor.y) && !IsTowardsPacman(startX, startY, neighbor.x, neighbor.y, pacmanX, pacmanY))
                    {
                        targetX = neighbor.x;
                        targetY = neighbor.y;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        currentSpeed_ = speed_;
        // Move towards Pac-Man
        targetX = static_cast<int>(pacmanX / maze_->GetTileWidth());
        targetY = static_cast<int>(pacmanY / maze_->GetTileHeight());
    }

    // Use A* to find a path
    std::vector<Node> path = FindPathBFS(startX, startY, targetX, targetY);

    if (!path.empty())
    {
        Node nextNode = path[path.size() - 2]; // Get the next step towards the target
        float targetWorldX = nextNode.x * maze_->GetTileWidth();
        float targetWorldY = nextNode.y * maze_->GetTileHeight();

        // Move ghost smoothly towards the next node
        float directionX = targetWorldX - x_;
        float directionY = targetWorldY - y_;
        float distance = std::sqrt(directionX * directionX + directionY * directionY);

        if (distance > 0.0f)
        {
            directionX /= distance;
            directionY /= distance;
        }

        if (distance > currentSpeed_)
        {
            x_ += directionX * currentSpeed_;
            y_ += directionY * currentSpeed_;
        }
        else
        {
            x_ = targetWorldX;
            y_ = targetWorldY;
        }
    }

    // Check if the ghost has reached its spawn position
    float radius = 70; // Define the radius within which the ghost is considered to be at the spawn position
    float distanceX = x_ - spawnX_ * 36;
    float distanceY = y_ - spawnY_ * 36;
    float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

    if (distance <= radius) // Check if within the specified radius
    {

        setEaten(false); // Set ghostEaten to false
        currentSpeed_ = speed_;
    }

    lastX_ = x_;
    lastY_ = y_;
}

bool EnemyChaseState::IsTowardsPacman(int startX, int startY, int targetX, int targetY, float pacmanX, float pacmanY)
{
    float ghostDirX = targetX - startX;
    float ghostDirY = targetY - startY;
    float pacmanDirX = static_cast<int>(pacmanX / maze_->GetTileWidth()) - startX;
    float pacmanDirY = static_cast<int>(pacmanY / maze_->GetTileHeight()) - startY;

    // Calculate dot product to determine if moving towards Pac-Man
    return (ghostDirX * pacmanDirX + ghostDirY * pacmanDirY) > 0;
}

void EnemyChaseState::Draw()
{
    // Draw the enemy texture at the specified position without applying color
    if (!pacman_->isPowerPelletEaten())
    {

        DrawTexture(enemyTexture_, static_cast<int>(x_), static_cast<int>(y_), raylib::Color::White());
    }
    // Check if the power pellet is eaten
    else // Replace with your actual condition for power pellet eaten
    {

        if (isEaten())
        {
            DrawTexture(ghostEaten_, static_cast<int>(x_), static_cast<int>(y_), raylib::Color::White());
        }
        else
            DrawTexture(scaredGhost_, static_cast<int>(x_), static_cast<int>(y_), raylib::Color::White());
    }
}
