#ifndef PHYSICS_FACTORY_HPP 
#define PHYSICS_FACTORY_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif


#include <memory>
#include <string>
#include <vector>
#include "PhysicsComponent.hpp"

/**
 * @brief Creates PhysicsComponents
 */
class PhysicsFactory{
    public:
		/**
		 * @brief Default constructor
		 */
        PhysicsFactory();

		/**
		 * @brief Default destructor
		 */
        ~PhysicsFactory();
	
		/**
		 * @brief Returns a pointer to a new PhysicsComponent
		 */
		PhysicsComponent* RequestComponent();

		/**
		 * @brief Frees all the PhysicsComponent created by the factory from memory
		 */
		void DeleteAll();


    private:
		std::vector<PhysicsComponent *> m_PhysicsList;

};


#endif
