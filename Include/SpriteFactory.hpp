#ifndef SPRITE_FACTORY_HPP 
#define SPRITE_FACTORY_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif


#include <memory>
#include <string>
#include <vector>
#include "SpriteComponent.hpp"


/**
 * @brief Creates SoundComponents
 */
class SpriteFactory{
    public:
		/**
		 * @brief Default constructor
		 */
        SpriteFactory();

		/**
		 * @brief Default destructor
		 */
        ~SpriteFactory();
	
		/**
		 * @brief Returns a pointer to a new SpriteComponent
		 */
		SpriteComponent* RequestComponent(int x, int y, int w, int h, int firstFrame, int lastFrame, 
						int spriteWidth, int spriteHeight, int spriteSheetRows, int spriteSheetCols, 
						std::string path, ResourceManager* rm, SDL_Renderer* ren);
		
		SpriteComponent* RequestComponent(ResourceManager* rm, SDL_Renderer* ren);
		/**
		* @brief Gives an SDL_Rect representing a camera to all the SpriteComponent created by the factory
		*/
		void ApplyCameraAll(SDL_Rect cam);
		
		/**
		* @brief Frees all the SpriteComponent created by the factory from memory
		*/
		void DeleteAll();


    private:
		std::vector<SpriteComponent *> m_SpriteList;

};


#endif
