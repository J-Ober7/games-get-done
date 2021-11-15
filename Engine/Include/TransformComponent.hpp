#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "Component.hpp"

/**
 * @brief A component which allows a GameObject to move
 */
class TransformComponent : public Component{
    public:
        /**
         * @brief Constructs a TransformComponent
         */
        TransformComponent();

        /**
         * @brief Destructs a TransformComponent
         */
        ~TransformComponent();

        /**
         * @brief Moves the gameObject's position by its velocity each frame
         */
        void Update(GameObject& gameObject);

};


#endif
