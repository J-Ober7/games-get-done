#ifndef SOUNDCOMPONENT_HPP 
#define SOUNDCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
#else // This works for Mac
    #include <SDL.h>
    #include <SDL_mixer.h>
#endif

#include "Component.hpp"

/**
 * @brief This Component plays music
 */
class SoundComponent : public Component{
    public:
        /**
         * @brief Loads and plays background music
         */
        SoundComponent();

        /**
         * @brief Stops playing background music
         */
        ~SoundComponent();

		/**
         * @brief Initializes a Sound Component
         */
		void init(const char* filePath);

        /**
         * @brief Does nothing.
         */
        void Update(GameObject & gameObject);
		/**
         * @brief Plays or resumes the music member
         */
		void Play();
		
		/**
         * @brief Pauses the music member
         */
		void Pause();
	
	private:
        /**
         * @brief Background music
         */
		Mix_Music* music;
	
};


#endif
