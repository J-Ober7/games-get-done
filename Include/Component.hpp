#ifndef COMPONENT_HPP 
#define COMPONENT_HPP

class GameObject;
#include "GameObject.hpp"
#include <string>

/**
 * @brief The type of collision. Where on the object did the collision occur
 */
enum CollisionType{
	Top, Bottom, Left, Right, NoCollision
};

/**
 * @brief Contains information about a collision, including CollisionType for specifying which face of this object is being collided with,
 * the tag of the other collider's game Object, and object penetration
 */
struct Collision{
    CollisionType type;
	std::string parentTag;
	int penetration;
};

/**
 * @brief An abstract Component of a GameObject. A Component determines the behavior of a GameObject.
 */
class Component{
    public:
		/**
		 * @brief Render the GameObject. The basic render does nothing.
		 */
		virtual void Render(SDL_Renderer* ren);
		
		/**
		 * @brief Update the state of the parent GameObject. Must be overriden by the child.
		 */
		virtual void Update(GameObject & gameObject) = 0;

		// holds a pointer to the parent of this component
		GameObject* parent;
};


#include <pybind11/pybind11.h>
/**
 * @brief Helper class that allows for abstract classes in pybind.
 * 
 */
class PyComponent : public Component{
	public:
		using Component::Component;

		void Update(GameObject & gameObject) override {
			PYBIND11_OVERLOAD_PURE(void, Component, Update, gameObject);
		}
};
#endif
