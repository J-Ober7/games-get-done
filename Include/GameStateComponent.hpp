#ifndef GS_COMPONENT
#define GS_COMPONENT

#include "Listener.hpp"
#include "Component.hpp"
#include <vector>

/**
 * @brief Component that can be attached to game objects that determines the current state of the game.
 * 
 */
class GameStateComponent : public Component {
    public:
        /**
         * @brief Default constructor
         */
        GameStateComponent();

        /**
         * @brief Default destructor
         */
        ~GameStateComponent();

        /**
         * @brief Updates the Game State and sends messages to it's listeners based on the parent game object.
         */
        void Update(GameObject & gameObject);

        /**
         * @brief Adds an object that will listen to any messages this component broadcasts.
         */
        void addListener(Listener* listener);

    private:
        std::vector<Listener*> m_listeners;
};

#endif