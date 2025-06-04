#include "GameplayState.h"

// Constructor implementation
GameplayState::GameplayState(float width, float height, gamePtr game)
    : screen_width_(width), screen_height_(height), game_(game), maze_(std::make_shared<Maze>(game))
{
    // Initialize Inky here with its parameters
}



// Initialize the gameplay state
void GameplayState::initialise()
{

    background_ = raylib::Texture2D(MAZEBACKPATH);                   // Update with your background filepath
    Image blinkyImage = LoadImage("../resources/sprites/blinky.png"); // Replace with the actual path to the texture image
    ImageResize(&blinkyImage, 40, 40);                                 // Resize the image to 36x36
    blinkyTexture_ = LoadTextureFromImage(blinkyImage);                // Create the texture from the resized image

    Image inkyImage = LoadImage("../resources/sprites/inky.png"); // Replace with the actual path to the texture image
    ImageResize(&inkyImage, 40, 40);                               // Resize the image to 36x36
    inkyTexture_ = LoadTextureFromImage(inkyImage);                // Create the texture from the resized image

    Image clydeImage = LoadImage("../resources/sprites/clyde.png"); // Replace with the actual path to the texture image
    ImageResize(&clydeImage, 40, 40);                                // Resize the image to 36x36
    clydeTexture_ = LoadTextureFromImage(clydeImage);                // Create the texture from the resized image

    Image pinkyImage = LoadImage("../resources/sprites/pinky.png"); // Replace with the actual path to the texture image
    ImageResize(&pinkyImage, 40, 40);                                // Resize the image to 36x36
    pinkyTexture_ = LoadTextureFromImage(pinkyImage);                // Create the texture from the resized image

    float clydeSpeed = 2.1;
    float inkySpeed = 2;
    float pinkySpeed = 2.9;
    float blinkySpeed = 2.4;
    float Radius = 20;
    float tileSize = 36;

    raylib::Color red = raylib::Color::Red();       // Blinky
    raylib::Color pink = raylib::Color::Pink();     // Pinky
    raylib::Color cyan = raylib::Color::SkyBlue();  // Inky
    raylib::Color orange = raylib::Color::Orange(); // Clyde

    pacman_ = std::make_shared<PacMan>(screen_width_ / 2, screen_height_ / 2 + 100, PACRADIUS, PACSPEED, maze_, game_);
    inky_ = Inky{9 * tileSize, 9 * tileSize, inkySpeed, Radius, maze_, cyan, pacman_, game_, inkyTexture_};
    blinky_ = Blinky{9 * tileSize, 8 * tileSize, blinkySpeed, Radius, maze_, pink, pacman_, game_, blinkyTexture_};
    pinky_ = Pinky{13 * tileSize, 9 * tileSize, pinkySpeed, Radius, maze_, red, pacman_, game_, pinkyTexture_};
    clyde_ = Clyde{13 * tileSize, 8 * tileSize, clydeSpeed, Radius, maze_, orange, pacman_, game_, clydeTexture_};

    // Load the maze
 if (!maze_->Load(mapName_))
    {
        std::cerr << "Failed to load map: " << mapName_ << std::endl;
    }
    maze_->LoadKeyMap("Maze");  // Load the key map

}

// Process player input
void GameplayState::processInput()
{
    pacman_->ProcessInput();
}

// Update game logic
void GameplayState::update()
{
    
    pacman_->Update();
    game_->characters.updateCharState();
    game_->characters.checkCollisions(pacman_);
}

// Draw everything on the screen
void GameplayState::draw()
{
    BeginDrawing();
    ClearBackground(raylib::Color::Black());

    raylib::Rectangle sourceRect{0, 0, static_cast<float>(background_.width), static_cast<float>(background_.height)};
    raylib::Rectangle destRect{0, 0, static_cast<float>(GAMEWIDTH), static_cast<float>(GAMEHEIGHT)};
    raylib::Vector2 origin{0, 0};
    ::DrawTexturePro(background_, sourceRect, destRect, origin, 0.0f, raylib::Color::White());
    maze_->Draw();
    pacman_->Draw();
   
    game_->characters.drawCharState(); // Draw character states

    EndDrawing();
}
