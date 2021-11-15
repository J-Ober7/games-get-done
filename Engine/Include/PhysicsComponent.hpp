#ifndef PHYSICSCOMPONENT_HPP
#define PHYSICSCOMPONENT_HPP

#include "Component.hpp"

/**
 * @brief A component which allows a GameObject to move
 */
class PhysicsComponent : public Component{
    public:
        /**
         * @brief Constructs a TransformComponent
         */
        PhysicsComponent();

        /**
         * @brief Destructs a TransformComponent
         */
        ~PhysicsComponent();

        /**
         * @brief Moves the gameObject's position by its velocity each frame
         */
        void Update(GameObject& gameObject);

        int m_Gravity{-2};
		int m_MaxGravity{-5};
		int m_MaxYVel{-10};

    private:
};


#endif
