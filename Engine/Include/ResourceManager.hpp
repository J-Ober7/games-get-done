#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>
#include <memory>
#include <iterator>
#include <iostream>
#include <SDL2/SDL.h>


/**
 * @brief Manages all the shared resources for the game, such as textures
 */
class ResourceManager{
public:

	/**
     * @brief Allows for the creation of only one ResourceManager
     */
	static ResourceManager& init();
	
	/**
     * @brief Destroys the ResourceManager
     */
	void destroy();

	/**
     * @brief Retrieves a texture from the given file path. If the texture has been accessed before, it won't make a new one
     */
	SDL_Texture* getTexture(SDL_Renderer* ren, std::string path); 

private:
	/**
     * @brief Private constructor for ResourceManager
     */
	ResourceManager();

	/**
     * @brief Private destructor for ResourceManager
     */
	~ResourceManager();
	

	/**
     * @brief Holds a map containing file paths and corresponding textures
     */
	std::map<std::string, SDL_Texture*> textureMap;

};

#endif
