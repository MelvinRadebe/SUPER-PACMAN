#ifndef MAZE_H
#define MAZE_H
#include <memory>
#include <raylib-cpp.hpp>
#include <vector>
#include <string>
#include <map>
#include <sstream>

#include "GameLoop.h"

#include <utility> // for std::pair
struct Game;

typedef std::shared_ptr<Game> gamePtr;

struct Tile
{
    char type;
    int orientation;
};

class Maze
{
public:
    Maze(gamePtr game) : game_(game){}
   
    ~Maze()
    {

        UnloadTexture(keyTexture_);
        UnloadTexture(fruitTexture_);
        UnloadTexture(powerPelletTexture_);
    }
    void LoadTextures();

    bool Load(const std::string &mazeName);

    void PrintMaze() const
    {
        for (const auto &row : maze_)
        {
            for (const auto &tile : row)
            {
      
            }
     
        }
    }

    void Draw();
    bool IsEmptySpace(int tileX, int tileY) const;
    size_t GetWidth() const { return maze_[0].size(); }
    size_t GetHeight() const { return maze_.size(); }
    const Tile &GetTile(int y, int x) const { return maze_[y][x]; }
    int GetTileWidth() const { return 36; }  // Assuming all tiles have the same width
    int GetTileHeight() const { return 36; } // Assuming all tiles have the same height
                                                   // Get the number of rows in the maze
    int GetRows() const { return maze_.size(); }
    bool IsWithinBounds(int tileX, int tileY) const
    {
        // Ensure the tile coordinates are within the dimensions of the maze
        return (tileX >= 0 && tileX < GetCols() && tileY >= 0 && tileY < GetRows());
    }

    // Get the number of columns in the maze
    int GetCols() const { return maze_.empty() ? 0 : maze_[0].size(); }
    bool IsBoundaryTile(int tileX, int tileY) const;
    void LoadKeyMap(const std::string &keyMapFilename);
    void OpenGateForKey(int keyX, int keyY);


    char GetTileType(int tileX, int tileY) const;
    void SetTile(int tileX, int tileY, char type);


private:
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> keyToGateMap; // Mapping keys to gates
    std::vector<std::vector<Tile>> maze_;

    Texture2D keyTexture_;
    Texture2D fruitTexture_;
    Texture2D powerPelletTexture_;
    Texture2D emptyTexture_;
    Texture2D wallTexture_;
    Texture2D cornerTexture_;
    Texture2D gateTexture_;
    

  


    Color gateColor = {139, 69, 19, 255};
    gamePtr game_ = std::make_shared<Game>();
    
  
};

#endif // MAZE_H
