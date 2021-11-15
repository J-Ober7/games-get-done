#ifndef TILE_H
#define TILE_H

#include <string>
#include "Component.hpp"
#include "GraphicsEngineRenderer.hpp"
#include "ResourceManager.hpp"
#include "CollisionComponent.hpp"

/**
 * @brief This is a minimal implementation of a TileMap
 */
class TileMapComponent : public Component{
public:
    
    TileMapComponent();
    /**
     * @brief Constructor for a tilemap
     */
    TileMapComponent(ResourceManager* rm, SDL_Renderer* ren);

    /**
     * @brief Destructor for a tilemap
     */
    ~TileMapComponent();

	/**
	 * @brief Initializes a TileMapComponent with a parallax value 1
     * tileSheetFileName is the path to the tile sheet file
     * rows and cols are dimentions of the tile sheet
     * _TileWidth and _TileHeight are the dimentions of a tile from the tile sheet
     * _mapX and _mapY are the dimentions of our tile map
     * ren is the renderer
	 */
	 void init(std::string tileSheetFileName, int rows, int cols, int spriteX, int spriteY, int _TileWidth, int _TileHeight, int _mapX, int _mapY);

    /**
	 * @brief Initializes a TileMapComponent
     * tileSheetFileName is the path to the tile sheet file
     * rows and cols are dimentions of the tile sheet
     * _TileWidth and _TileHeight are the dimentions of a tile from the tile sheet
     * _mapX and _mapY are the dimentions of our tile map
     * ren is the renderer
     * para is the parallax value
	 */
	 void init(std::string tileSheetFileName, int rows, int cols, int spriteX, int spriteY, int _TileWidth, int _TileHeight, int _mapX, int _mapY, float para);
    
    /**
     * @brief Add a tile type to the list of impassable/collidable tiles for this tile map
     */
    void addCollidableTile(int tileType);

    /**
     * @brief Generates an example map
     */
    void GenerateSimpleMap();

    /**
     * @brief Generates an example map
     */
	void GenerateBGMap();

    /**
     * @brief Function for printing text to console
     */
    void PrintMap();

    /**
     * @brief Set the 'type' of tile at an x and y position
     */
    void SetTile(int x, int y, int type);

    /**
     * @brief Return the tile type at an x and y position
     */
    int GetTileType(int x, int y);

    /**
     * @brief Does nothing
     */
    void Update(GameObject& gameObject);

    /**
     * @brief Draw all of the tiles in the tilemap
     */
    void Render(SDL_Renderer* renderer) override;
    
	/**
     * @brief Gives the Component a camera perspective
     */
	void ApplyCamera(SDL_Rect cam);

    /**
     * @brief Given a bounding box, find the tile types for each of the four corners of the bounding box
     * and determine if any of the tiles are impassable/create a collision.
     */
    void CheckCollsion(CollisionComponent * collider);

    // How big each tile is.
    int m_TileWidth;
    int m_TileHeight;
    
    // size of our tilemap
    int m_MapX;
    int m_MapY; 

    bool background{false};

    float parallax;
	bool debug{false};

private:
    // Dimensions of our TileMap's Sprite Sheet and individual tiles.
    // Used for spiltting up the sprite sheet
    int m_Rows;
    int m_Cols;
	
	int m_spriteTileX;
	int m_spriteTileY;
	
    // the path to our tile set file
    std::string fileName;
    SDL_Texture *m_Texture;

    // Where our TileMap is rendered
	SDL_Rect camera;
	SDL_Rect position;

    // Stores our tile types
    int* m_Tiles;

    // stores the tile types that cannot be passed through and can be collided with
    std::vector<int> impassableTileTypes;

	ResourceManager* m_rm;
    SDL_Renderer* m_ren;
};

#endif
