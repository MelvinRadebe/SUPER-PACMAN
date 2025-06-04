#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <raylib-cpp.hpp>
#include "GameLoop.h"
#include "Maze.h"
#include "GameSettings.h"
#include "PacMan.h"
#include "GameplayState.h"
#include <iostream>

raylib::Window window(GAMEWIDTH, GAMEHEIGHT, "Pac-Man Game");


TEST_CASE("PacMan moves correctly in the UP direction")
{
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);
    // Create a shared pointer for the Maze
    auto maze = std::make_shared<Maze>(Ptr);
    maze->Load("maze");
    maze->LoadKeyMap("maze");
    
    auto InitialPosY = GAMEHEIGHT / 2;
    auto InitialPosX = GAMEWIDTH / 2;

    // Pass the shared pointer of the maze to PacMan
    PacMan pacman{InitialPosX, InitialPosY, PACRADIUS, PACSPEED, maze, Ptr};
    pacman.SetDirection(Direction::UP);
    pacman.Update();
    
    float expectedPosY = InitialPosY - PACSPEED;
    
    CHECK(pacman.getPosition().x == InitialPosX);
    CHECK(pacman.getPosition().y == expectedPosY);
}



TEST_CASE("PacMan moves correctly in the DOWN direction")
{
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);
     auto maze = std::make_shared<Maze>(Ptr);
    maze->Load("maze");
    maze->LoadKeyMap("maze");
    auto InitialPosY = GAMEHEIGHT / 2;
    auto InitialPosX = GAMEWIDTH / 2;
    PacMan pacman{InitialPosX, InitialPosY, PACRADIUS, PACSPEED, maze, Ptr};
    pacman.SetDirection(Direction::DOWN);
    pacman.Update();
    float expectedPosY = InitialPosY + PACSPEED;
    CHECK(pacman.getPosition().x == InitialPosX);
    CHECK(pacman.getPosition().y == expectedPosY);
}

TEST_CASE("PacMan moves correctly in the RIGHT direction")
{
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);
    auto maze = std::make_shared<Maze>(Ptr);
    maze->Load("maze");
    maze->LoadKeyMap("maze");
    auto InitialPosY = GAMEHEIGHT / 2;
    auto InitialPosX = GAMEWIDTH / 2;
    PacMan pacman{InitialPosX, InitialPosY, PACRADIUS, PACSPEED, maze, Ptr};
    pacman.SetDirection(Direction::RIGHT);
    pacman.Update();
    float expectedPosX = InitialPosX + PACSPEED;
    CHECK(pacman.getPosition().x == expectedPosX);
    CHECK(pacman.getPosition().y == InitialPosY);
}

TEST_CASE("PacMan moves correctly in the LEFT direction")
{
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);
    auto maze = std::make_shared<Maze>(Ptr);
    maze->Load("maze");
    maze->LoadKeyMap("maze");
    auto InitialPosY = GAMEHEIGHT / 2;
    auto InitialPosX = GAMEWIDTH / 2;
    PacMan pacman{InitialPosX, InitialPosY, PACRADIUS, PACSPEED, maze, Ptr};
    pacman.SetDirection(Direction::LEFT);
    pacman.Update();
    float expectedPosX = InitialPosX - PACSPEED;
    CHECK(pacman.getPosition().x == expectedPosX);
    CHECK(pacman.getPosition().y == InitialPosY);
}

TEST_CASE("PacMan does not move into walls")
{
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);
     auto maze = std::make_shared<Maze>(Ptr);
    maze->Load("MazeWithWalls");
    auto InitialPosY = GAMEHEIGHT / 2;
    auto InitialPosX = GAMEWIDTH / 2;
    PacMan pacman{InitialPosX, InitialPosY, PACRADIUS, PACSPEED, maze, Ptr};
    std::vector<Direction> directions = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};

    for (const auto &direction : directions)
    {
        pacman.SetDirection(direction);
        pacman.Update();
        CHECK(pacman.getPosition().x == InitialPosX);
        CHECK(pacman.getPosition().y == InitialPosY);
    }
}

TEST_CASE("PacMan's initial positioning arguments are set correctly")
{
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);
    auto maze = std::make_shared<Maze>(Ptr);
    maze->Load("maze");
    maze->LoadKeyMap("maze");
    auto InitialPosY = GAMEHEIGHT / 2;
    auto InitialPosX = GAMEWIDTH / 2;
    PacMan pacman{InitialPosX, InitialPosY, PACRADIUS, PACSPEED, maze, Ptr};
    CHECK(pacman.getPosition().x == InitialPosX);
    CHECK(pacman.getPosition().y == InitialPosY);
}

TEST_CASE("PacMan's position remains unchanged when attempting to move beyond the top boundary")
{
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);
     auto maze = std::make_shared<Maze>(Ptr);
    maze->Load("maze");
    maze->LoadKeyMap("maze");
    auto InitialPosY = GAMEHEIGHT;
    auto InitialPosX = GAMEWIDTH / 2;
    PacMan pacman{InitialPosX, InitialPosY, PACRADIUS, PACSPEED, maze, Ptr};
    pacman.SetDirection(Direction::UP);
    pacman.Update();
    CHECK(pacman.getPosition().x == InitialPosX);
    CHECK(pacman.getPosition().y == InitialPosY);
}

TEST_CASE("PacMan's position remains unchanged when attempting to move beyond the bottom boundary")
{
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);
     auto maze = std::make_shared<Maze>(Ptr);
    maze->Load("maze");
    maze->LoadKeyMap("maze");
    auto InitialPosY = GAMEHEIGHT;
    auto InitialPosX = GAMEWIDTH / 2;
    PacMan pacman{InitialPosX, InitialPosY, PACRADIUS, PACSPEED, maze, Ptr};
    pacman.SetDirection(Direction::DOWN);
    pacman.Update();
    CHECK(pacman.getPosition().x == InitialPosX);
    CHECK(pacman.getPosition().y == InitialPosY);
}



TEST_CASE("Clyde movement in GameplayState")
{
    // Initialize game object and dependencies
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);

    gameplayState.setMapName("Empty");
    // Initialize the gameplay state with textures, maze, and characters
    gameplayState.initialise();

    // Retrieve Clyde's initial position
    float initialX = gameplayState.getClyde().getPosition().x;
    float initialY = gameplayState.getClyde().getPosition().y;

    // Retrieve Pac-Man's initial position
    float pacmanX = gameplayState.getPacMan()->getPosition().x;
    float pacmanY = gameplayState.getPacMan()->getPosition().y;

    // Calculate initial distance between Clyde and Pac-Man
    float initialDistance = sqrt(pow(pacmanX - initialX, 2) + pow(pacmanY - initialY, 2));

    // Simulate some updates to test movement
    int numUpdates = FPS * 2; // Simulating four seconds of updates
    for (int i = 0; i < numUpdates; ++i)
    {
        gameplayState.update(); // Updates the state, including Clyde's movement
    }

    float newX = gameplayState.getClyde().getPosition().x;
    float newY = gameplayState.getClyde().getPosition().y;

    // Calculate new distance between Clyde and Pac-Man
    float newDistance = sqrt(pow(pacmanX - newX, 2) + pow(pacmanY - newY, 2));

    // Check that Clyde has moved from the initial position
    CHECK(newX != initialX); // Clyde's X position should change
    CHECK(newY != initialY); // Clyde's Y position should change


}

TEST_CASE("Inky movement in GameplayState")
{
    // Initialize game object and dependencies
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);
    

    gameplayState.setMapName("Empty");
    // Initialize the gameplay state with textures, maze, and characters
    gameplayState.initialise();

    // Retrieve Clyde's initial position
    float initialX = gameplayState.getInky().getPosition().x;
    float initialY = gameplayState.getInky().getPosition().y;

    // Retrieve Pac-Man's initial position
    float pacmanX = gameplayState.getPacMan()->getPosition().x;
    float pacmanY = gameplayState.getPacMan()->getPosition().y;

    // Calculate initial distance between Clyde and Pac-Man
    float initialDistance = sqrt(pow(pacmanX - initialX, 2) + pow(pacmanY - initialY, 2));

    // Simulate some updates to test movement
    int numUpdates = FPS * 2; // Simulating four seconds of updates
    for (int i = 0; i < numUpdates; ++i)
    {
        gameplayState.update(); // Updates the state, including Clyde's movement
    }

    float newX = gameplayState.getInky().getPosition().x;
    float newY = gameplayState.getInky().getPosition().y;

    // Calculate new distance between Clyde and Pac-Man
    float newDistance = sqrt(pow(pacmanX - newX, 2) + pow(pacmanY - newY, 2));

    // Check that Clyde has moved from the initial position
    CHECK(newX != initialX); // Clyde's X position should change
    CHECK(newY != initialY); // Clyde's Y position should change
    CHECK(initialDistance>newDistance);


}
TEST_CASE("Blinky movement in GameplayState")
{
    // Initialize game object and dependencies
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);
    

    gameplayState.setMapName("Empty");
    // Initialize the gameplay state with textures, maze, and characters
    gameplayState.initialise();

    // Retrieve Clyde's initial position
    float initialX = gameplayState.getBlinky().getPosition().x;
    float initialY = gameplayState.getBlinky().getPosition().y;

    // Retrieve Pac-Man's initial position
    float pacmanX = gameplayState.getPacMan()->getPosition().x;
    float pacmanY = gameplayState.getPacMan()->getPosition().y;
    gameplayState.getPacMan()->setPowerPelletMode(true);


    // Calculate initial distance between Clyde and Pac-Man
    float initialDistance = sqrt(pow(pacmanX - initialX, 2) + pow(pacmanY - initialY, 2));

    // Simulate some updates to test movement
    int numUpdates = FPS * 2; // Simulating four seconds of updates
    for (int i = 0; i < numUpdates; ++i)
    {
        gameplayState.update(); // Updates the state, including Clyde's movement
    }

    float newX = gameplayState.getBlinky().getPosition().x;
    float newY = gameplayState.getBlinky().getPosition().y;

    // Calculate new distance between Clyde and Pac-Man
    float newDistance = sqrt(pow(pacmanX - newX, 2) + pow(pacmanY - newY, 2));

    // Check that Clyde has moved from the initial position
    CHECK(newX != initialX); 
    CHECK(newY != initialY); 
    CHECK(initialDistance>newDistance);


}
TEST_CASE("Pinky movement in GameplayState")
{
    // Initialize game object and dependencies
    auto Ptr = std::make_shared<Game>();
GameplayState gameplayState(GAMEWIDTH, GAMEHEIGHT, Ptr);
    

    gameplayState.setMapName("Empty");
    // Initialize the gameplay state with textures, maze, and characters
    gameplayState.initialise();

    // Retrieve Clyde's initial position
    float initialX = gameplayState.getPinky().getPosition().x;
    float initialY = gameplayState.getPinky().getPosition().y;

    // Retrieve Pac-Man's initial position
    float pacmanX = gameplayState.getPacMan()->getPosition().x;
    float pacmanY = gameplayState.getPacMan()->getPosition().y;

    // Calculate initial distance between Clyde and Pac-Man
    float initialDistance = sqrt(pow(pacmanX - initialX, 2) + pow(pacmanY - initialY, 2));

    // Simulate some updates to test movement
    int numUpdates = FPS * 2; // Simulating four seconds of updates
    for (int i = 0; i < numUpdates; ++i)
    {
        gameplayState.update(); // Updates the state, including Clyde's movement
    }

    float newX = gameplayState.getPinky().getPosition().x;
    float newY = gameplayState.getPinky().getPosition().y;

    // Calculate new distance between Clyde and Pac-Man
    float newDistance = sqrt(pow(pacmanX - newX, 2) + pow(pacmanY - newY, 2));

    // Check that Clyde has moved from the initial position
    CHECK(newX != initialX); // Clyde's X position should change
    CHECK(newY != initialY); // Clyde's Y position should change
    CHECK(initialDistance>newDistance);


}