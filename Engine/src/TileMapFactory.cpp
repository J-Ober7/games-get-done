#include "TileMapFactory.hpp"

TileMapFactory::TileMapFactory(){}
TileMapFactory::~TileMapFactory(){}

TileMapComponent* TileMapFactory::RequestComponent(std::string tileSheetFileName, int rows, int cols, int spriteX, int spriteY, int _TileWidth, int _TileHeight, int _mapX, int _mapY, ResourceManager* rm, SDL_Renderer* ren)
{
	TileMapComponent* tmc = new TileMapComponent(rm, ren);
	tmc->init(tileSheetFileName,rows,cols, spriteX, spriteY,_TileWidth,_TileHeight,_mapX,_mapY);
	m_tileMaps.push_back(tmc);
	return tmc;	
}

TileMapComponent* TileMapFactory::RequestComponent(std::string tileSheetFileName, int rows, int cols, int spriteX, int spriteY, int _TileWidth, int _TileHeight, int _mapX, int _mapY, ResourceManager* rm, SDL_Renderer* ren, float para) {
	TileMapComponent* tmc = new TileMapComponent(rm, ren);
	tmc->init(tileSheetFileName,rows,cols, spriteX, spriteY,_TileWidth,_TileHeight,_mapX,_mapY, para);
	m_tileMaps.push_back(tmc);
	return tmc;	
}


TileMapComponent* TileMapFactory::RequestComponent(ResourceManager* rm, SDL_Renderer* ren)
{
	TileMapComponent* tmc = new TileMapComponent(rm, ren);
	m_tileMaps.push_back(tmc);
	return tmc;	
}
/**
* Prints the tile index map of all the TileMap components created by the factory
*/
void TileMapFactory::PrintMaps(){
	for(int i = 0; i < m_tileMaps.size(); i++){
		m_tileMaps[i]->PrintMap();
		
	}
	
}

/**
* Gives an SDL_Rect representing a camera to all the TileMap components created by the factory
*/
void TileMapFactory::ApplyCameraAll(SDL_Rect cam){
	for(int i = 0; i < m_tileMaps.size(); i++){
		m_tileMaps[i]->ApplyCamera(cam);
		
	}
	
}
/**
* Frees all the TileMap components created by the factory from memory
*/
void TileMapFactory::DeleteAll(){
	for(int i = 0; i < m_tileMaps.size(); i++){
		delete(m_tileMaps[i]);
		
	}
}

