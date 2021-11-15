
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

// I recommend a map for filling in the resource manager
#include <map>
#include <string>
#include <memory>
#include <iterator>

#include "ResourceManager.hpp"

ResourceManager::ResourceManager(){
	
}


ResourceManager::~ResourceManager(){

	
}

ResourceManager& ResourceManager::init(){
	static ResourceManager *instance = new ResourceManager();
    return *instance;
}

void ResourceManager::destroy(){
	// deletes all entries from the map
	std::map< std::string, SDL_Texture* >::iterator it;
	for (it = textureMap.begin(); it != textureMap.end(); it++) {
		SDL_DestroyTexture(it->second);
		it = textureMap.erase(it);
	}
}

SDL_Texture* ResourceManager::getTexture(SDL_Renderer* ren, std::string path){
	
	auto tim = textureMap.find(path);
	//SDL_Log(tim->first.c_str());
	if(tim == textureMap.end()){
	
		const char* c = path.c_str();
		SDL_Surface *spriteSheet = SDL_LoadBMP(c);
		if(spriteSheet==NULL){
			//SDL_Log("Failed to allocate surface");
		}else{
			SDL_Log("Allocated a bunch of memory to create texture of image to add to map");
			// Create a texture from our surface
			// Textures run faster and take advantage of hardware acceleration
			SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, spriteSheet);

			textureMap.insert(std::make_pair(path, texture));
			
			tim = textureMap.find(path);
		}
	}
	
	return tim->second;
}
