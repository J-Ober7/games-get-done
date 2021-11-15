
#include "SpriteFactory.hpp"

SpriteFactory::SpriteFactory(){}
SpriteFactory::~SpriteFactory(){}

/**
* Returns a pointer to a new TileMapComponent
*/
SpriteComponent* SpriteFactory::RequestComponent(int x, int y, int w, int h, int firstFrame, int lastFrame, 
						int spriteWidth, int spriteHeight, int spriteSheetRows, int spriteSheetCols, 
						std::string path, ResourceManager* rm, SDL_Renderer* ren){	
	SpriteComponent* sc = new SpriteComponent(rm, ren);
	sc->init(x, y, w, h, firstFrame, lastFrame, spriteWidth, spriteHeight, spriteSheetRows, spriteSheetCols, path);
	m_SpriteList.push_back(sc);
	return sc;	
	
}

SpriteComponent* SpriteFactory::RequestComponent(ResourceManager* rm, SDL_Renderer* ren){
	
	SpriteComponent* sc = new SpriteComponent(rm, ren);
	m_SpriteList.push_back(sc);
	return sc;	
}

/**
* Gives an SDL_Rect representing a camera to all the Sprite components created by the factory
*/
void SpriteFactory::ApplyCameraAll(SDL_Rect cam){
	for(int i = 0; i < m_SpriteList.size(); i++){
		m_SpriteList[i]->ApplyCamera(cam);
		
	}
}

/**
* Frees all the Sprite components created by the factory from memory
*/
void SpriteFactory::DeleteAll(){
	for(int i = 0; i < m_SpriteList.size(); i++){
		delete(m_SpriteList[i]);
		
	}
}
