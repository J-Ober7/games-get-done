#ifndef COLLISIONCOMPONENT_HPP 
#define COLLISIONCOMPONENT_HPP

//class Component;
#include "Component.hpp"

/**
 * @brief A Component which allows the gameObject to collide with other collidable objects
 */
class CollisionComponent : public Component{
    public:
        /**
         * @brief Default constructor
         */
        CollisionComponent();

        /**
         * @brief Default destructor
         */
        ~CollisionComponent();
		/**
         * @brief Initializes Collision
		 * gameObject is the gameObject it will be attached to
         */
		void init(GameObject* gameObject);

        /**
         * @brief Updates the collider hitbox
         */
        void Update(GameObject & gameObject);

        void Render(SDL_Renderer* renderer) override;

		/**
         * @brief Sets the size of the collider
         */
        void SetColliderSize(int width, int height);

        /**
         * @brief Check against the other collision component to detect any collisions. Assume that
         * both objects have already been moved appropriately.
         */
		Collision* CheckCollision(CollisionComponent & other);

        /**
         * @brief Adjust the parent GameObject appropriately based on this collision.
         */
        void HandleCollision();

        // holds a pointer to the parent of this component
        GameObject* parent;
		
        // can the parent object be moved based on collisions?
		bool isMovable{false};
    private:
        // represents the bounding box for this collider component
        SDL_Rect collider;
        
};


#endif