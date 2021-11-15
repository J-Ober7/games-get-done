#ifndef COLLISION_SYSTEM
#define COLLISION_SYSTEM

#include "CollisionComponent.hpp"
#include "TileMapFactory.hpp"
#include <vector>
/**
 * @brief This may function as more of a factory class, but for now, this is the collision module
 * that will hold all the collisions, and check each frame for collisions between two colliders
 * 
 */
class CollisionSystem {
    public:

        /**
         * @brief Construct a new Collision System object
         * 
         */
        CollisionSystem();

        /**
         * @brief Destroy the Collision System object
         * 
         */
        ~CollisionSystem();

        /**
         * Initialize this collision system with the given tile map factory
         */
        void init(TileMapFactory* factory);

        /**
         * @brief Free any memory associated with the collision componenets
         * 
         */
        void shutDown();

        /**
         * Create a new Collision component and return a pointer to the newly created collision component
         */
        CollisionComponent* RequestComponent();

        /**
         * For all collider components created through this factory, check all of them against each other
         * and the tilemaps in the game to determine collisions in the scene.
         */
        void checkCollisions();
		/**
         * Tells all the collider componenets created through this factory to handle their collisions
         */
        void handleCollisions();
    
    private:
        std::vector<CollisionComponent *> GameColliders;
        TileMapFactory* tmf;
};

#endif