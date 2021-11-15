#ifndef TRANSFORM_FACTORY_HPP 
#define TRANSFORM_FACTORY_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif


#include <memory>
#include <string>
#include <vector>
#include "TransformComponent.hpp"

/**
 * @brief Creates TransformComponents
 */
class TransformFactory{
    public:
		/**
		 * @brief Default constructor
		 */
        TransformFactory();

		/**
		 * @brief Default destructor
		 */
        ~TransformFactory();
	
		/**
		 * @brief Returns a pointer to a new TransformComponent
		 */
		TransformComponent* RequestComponent();

		/**
		* @brief Frees all the Transform components created by the factory from memory
		*/
		void DeleteAll();


    private:
		std::vector<TransformComponent *> m_TransformList;

};


#endif
