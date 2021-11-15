#ifndef SOUND_FACTORY_HPP 
#define SOUND_FACTORY_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif


#include <memory>
#include <string>
#include <vector>
#include "SoundComponent.hpp"

/**
 * @brief Creates SoundComponents
 */
class SoundFactory{
    public:
		/**
		 * @brief Default constructor
		 */
        SoundFactory();

		/**
		 * @brief Default destructor
		 */
        ~SoundFactory();
	
		/**
		 * @brief Returns a pointer to a new SoundComponent
		 */
		SoundComponent* RequestComponent(const char* filePath);

		// TODO
		SoundComponent* RequestComponent();

		/**
		* @brief Frees all the SoundComponent created by the factory from memory
		*/
		void DeleteAll();


    private:
		std::vector<SoundComponent *> m_SoundList;

};


#endif
