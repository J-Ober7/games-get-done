#include "GameStateComponent.hpp"
/**
         * @brief Default constructor
         */
GameStateComponent::GameStateComponent() {}

/**
         * @brief Default destructor
         */
GameStateComponent::~GameStateComponent() {}

/**
         * @brief Updates the Game State and sends messages to it's listeners based on the parent game object.
         */
void GameStateComponent::Update(GameObject &gameObject)
{
    // loop through collisions. If the gameObject has a player tag and there is a collision with an enemy,
    // broadcast a game over message to listeners
    if (gameObject.m_tag == "player")
    {
        // check if player is out of bounds - if so, game over
        if (gameObject.position.y < 0 || gameObject.position.y > 1000 || gameObject.position.x < -500 || gameObject.position.x > 3000)
        {
            for (int j = 0; j < m_listeners.size(); j++)
            {
                m_listeners[j]->receive(1);
            }
            return;
        }
        for (int i = 0; i < gameObject.collisions.size(); i++)
        {
            Collision currCollision = *(gameObject.collisions[i]);
            if (currCollision.parentTag == "enemy" && currCollision.type != CollisionType::NoCollision)
            {
                for (int j = 0; j < m_listeners.size(); j++)
                {
                    m_listeners[j]->receive(1);
                }
                break;
            }
        }
    }
}

/**
         * @brief Adds an object that will listen to any messages this component broadcasts.
         */
void GameStateComponent::addListener(Listener *listener)
{
    m_listeners.push_back(listener);
}