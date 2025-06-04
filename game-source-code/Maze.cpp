#include "GameSettings.h"
#include "Maze.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>

// Constructor

// Load the maze from a file
bool Maze::Load(const std::string &mazeName)
{
    std::ifstream layoutFile(MAZEDIR + mazeName + "_layout.txt");
    std::ifstream orientationFile(MAZEDIR + mazeName + "_orientations.txt");

    if (!layoutFile.is_open() || !orientationFile.is_open())
    {
        std::cerr << "Error opening maze files." << std::endl;
        return false;
    }

    std::string layoutLine, orientationLine;
    while (std::getline(layoutFile, layoutLine) && std::getline(orientationFile, orientationLine))
    {
        std::vector<Tile> row;
        for (size_t i = 0; i < layoutLine.size(); ++i)
        {
            Tile tile;
            tile.type = layoutLine[i];
            tile.orientation = orientationLine[i] - '0'; // Convert char to int
            row.push_back(tile);
        }
        maze_.push_back(row);
    }

    layoutFile.close();
    orientationFile.close();

    // Load the textures (make sure file paths are correctly defined)
    Image keyImage = LoadImage(KEYPATH);     // Replace with the actual path to the texture image
    ImageResize(&keyImage, 36, 36);               // Resize the image to 36x36
    keyTexture_ = LoadTextureFromImage(keyImage); // Create the texture from the resized image

    Image fruitImage = LoadImage(CHERRYPATH);    // Replace with the actual path to the texture image
    ImageResize(&fruitImage, 36, 36);                 // Resize the image to 36x36
    fruitTexture_ = LoadTextureFromImage(fruitImage); // Create the texture from the resized image

    powerPelletTexture_ = LoadTexture(POWERPELLETPATH);
    emptyTexture_ = LoadTexture(EMPTYPATH);
    wallTexture_ = LoadTexture(WALPATH);
    cornerTexture_ = LoadTexture(CORNERPATH);
    gateTexture_ = LoadTexture(GATEPATH);
    

    return true;
}

// Draw the maze
// Draw the maze
// Draw the maze
// Draw the maze
// Draw the maze
void Maze::Draw()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Calculate the size of each tile based on the original maze dimensions
    float tileWidth = static_cast<float>(emptyTexture_.width);
    float tileHeight = static_cast<float>(emptyTexture_.height);

    // Calculate the total width and height of the maze
    float mazeWidth = tileWidth * maze_[0].size();
    float mazeHeight = tileHeight * maze_.size();

    // Calculate the offsets to center the maze on the screen
    float screenOffsetX = (screenWidth - mazeWidth) / 2;
    float screenOffsetY = (screenHeight - mazeHeight) / 2;

    // Maze-specific drawing offsets (customize as needed)
    float mazeOffsetX = 20; // Additional X offset for maze
    float mazeOffsetY = 15; // Additional Y offset for maze

    // Loop through each tile in the maze data structure (2D array)
    for (size_t y = 0; y < maze_.size(); ++y)
    {
        for (size_t x = 0; x < maze_[y].size(); ++x)
        {
            Tile tile = maze_[y][x]; // Get the current tile at (x, y)
            Texture2D texture;       // Reference for the current texture to draw

            // Determine the texture to use based on the tile type
            switch (tile.type)
            {
            case 'W':
                texture = wallTexture_; // Wall texture
                break;
            case 'C':
                texture = cornerTexture_; // Corner texture
                break;
            case 'G':
                texture = gateTexture_; // Gate texture
                break;
            case 'K':
                texture = keyTexture_; // Key texture
                break;
            case 'F':
                texture = fruitTexture_; // Fruit texture
                break;
            case 'P':
                texture = powerPelletTexture_; // Power pellet texture
                break;
            default:
                // For empty spaces ('E'), we do not draw anything
                continue; // Skip drawing this tile
            }

            // Draw the texture with rotation
            Rectangle source = {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
            Rectangle dest = {
                x * tileWidth + screenOffsetX + mazeOffsetX,
                y * tileWidth + screenOffsetY + mazeOffsetY,
                tileWidth, tileWidth};
            Vector2 origin = {tileWidth / 2.0f, tileWidth / 2.0f}; // Center of the tile

            // If the tile is a gate, draw the broken gate texture on top
    
            DrawTexturePro(texture, source, dest, origin, tile.orientation * 90.0f, WHITE);
        }
    }
}

// Check if a tile is empty or a key
bool Maze::IsEmptySpace(int x, int y) const
{
    // Check if the coordinates are within bounds of the maze
    if (y < 0 || y >= maze_.size() || x < 0 || x >= maze_[y].size())
    {
        return false; // Out of bounds
    }

    char tileType = maze_[y][x].type;

    // Check for 'E' (empty space), 'K' (key), 'F' (fruit), 'P' (power pellet), or 'S' (special)
    return tileType == 'E' || tileType == 'K' || tileType == 'F' || tileType == 'P' || tileType == 'S';
}

// Check if a tile is a boundary corner
bool Maze::IsBoundaryTile(int tileX, int tileY) const
{
    // Check if the tile itself is a corner
    return GetTile(tileY, tileX).type == 'C';
}

void Maze::LoadKeyMap(const std::string &keyMapFilename)
{
    std::ifstream keyMapFile(MAZEDIR + keyMapFilename + "_keymap.txt");
    if (!keyMapFile.is_open())
    {
        std::cerr << "Error opening key map file: " << keyMapFilename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(keyMapFile, line))
    {
        std::istringstream keyLineStream(line);
        int keyX, keyY;
        keyLineStream >> keyX >> keyY;

        std::vector<std::pair<int, int>> gateCoordinates;
        if (std::getline(keyMapFile, line))
        { // Read gates line
            std::istringstream gateLineStream(line);
            int gateX, gateY;
            while (gateLineStream >> gateX >> gateY)
            {
                gateCoordinates.push_back({gateX, gateY});
            }
        }

        // Store the key and its associated gates
        keyToGateMap[{keyX, keyY}] = gateCoordinates;
    }

    keyMapFile.close();
}

// Function to open gates associated with a collected key
void Maze::OpenGateForKey(int keyX, int keyY)
{
    auto keyPosition = std::make_pair(keyX, keyY);

    // Check if the key has corresponding gates
    if (keyToGateMap.find(keyPosition) != keyToGateMap.end())
    {
        for (const auto &gatePosition : keyToGateMap[keyPosition])
        {
            int gateX = gatePosition.first;
            int gateY = gatePosition.second;

            // Open the gate by setting the tile to an empty space 'E'
            if (maze_[gateY][gateX].type == 'G')
            {
                maze_[gateY][gateX].type = 'E';
            }
            else
            {
            }
        }
    }
    else
    {
    }
}

// Get the type of tile at (tileX, tileY)
char Maze::GetTileType(int tileX, int tileY) const
{
    // Check if the tile coordinates are within bounds
    if (IsWithinBounds(tileX, tileY))
    {
        return maze_[tileY][tileX].type; // Return the type of the tile
    }
    return ' '; // Return an empty space if out of bounds
}

// Set the type of tile at (tileX, tileY)
void Maze::SetTile(int tileX, int tileY, char type)
{
    // Check if the tile coordinates are within bounds
    if (IsWithinBounds(tileX, tileY))
    {
        maze_[tileY][tileX].type = type; // Set the new tile type
    }
}
