#ifndef LISTENER
#define LISTENER

/**
 * @brief Class to hold a basic listener for a messaging system. Allows listener to 
 * receive messages from whoever it is subscribed to.
 */
class Listener {
    public:
        /**
         * @brief Destroy the Listener object
         * 
         */
        virtual ~Listener() {};
        /**
         * @brief Handle the given message ID appropriately.
         * 
         * @param messageID represents the id correlating with a specific type of message
         */
        virtual void receive(int messageID) = 0;
    private:
};

#endif