#ifndef TILEMAP_FACTORY_HPP 
#define TILEMAP_FACTORY_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif


#include <memory>
#include <string>
#include <vector>
#include "TileMapComponent.hpp"

/**
 * @brief Creates TileMapComponents
 */
class TileMapFactory{
    public:
		/**
		 * @brief Default constructor
		 */
        TileMapFactory();

		/**
		 * @brief Default destructor
		 */
        ~TileMapFactory();
	
		/**
		 * @brief Returns a pointer to a new TileMapComponent initialized with parallax value 1
		 * tileSheetFileName is the path to the tile sheet
		 * rows and cols are the dimentions of the tile sheet
		 * _TileWidth and _TileHeight are the dimentions of a tile
		 * _mapX and _mapY are the dimentions of the tile map
		 */
		TileMapComponent* RequestComponent(std::string tileSheetFileName, int rows, int cols, int spriteX, int spriteY, int _TileWidth,
												int _TileHeight, int _mapX, int _mapY, ResourceManager* rm, SDL_Renderer* ren);
		
		/**
		 * @brief Returns a pointer to a new TileMapComponent
		 * tileSheetFileName is the path to the tile sheet
		 * rows and cols are the dimentions of the tile sheet
		 * _TileWidth and _TileHeight are the dimentions of a tile
		 * _mapX and _mapY are the dimentions of the tile map
		 * para is the parallax value
		 */
		TileMapComponent* RequestComponent(std::string tileSheetFileName, int rows, int cols, int spriteX, int spriteY, int _TileWidth,
												int _TileHeight, int _mapX, int _mapY, ResourceManager* rm, SDL_Renderer* ren, float para);
		
		TileMapComponent* RequestComponent(ResourceManager* rm, SDL_Renderer* ren);
		/**
		* @brief Prints the tile index map of all the TileMap components created by the factory
		*/
		void PrintMaps();

		/**
		* @brief Gives an SDL_Rect representing a camera to all the TileMap components created by the factory
		*/
		void ApplyCameraAll(SDL_Rect cam);

		/**
		* @brief Frees all the TileMap components created by the factory from memory
		*/
		void DeleteAll();

		std::vector<TileMapComponent *> m_tileMaps;
};


#endif
