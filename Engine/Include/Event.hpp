#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

/**
 * @brief A custom structure to wrap key event input from SDL_Events
 * - type: Either "mouse" or "key" to represent a mouse or key event
 * - id: The button or key pressed
 * - isDown:  a boollean wherefalse for up, true for down
 */
struct InputEvent
{
    // Either "mouse" or "key" to represent a mouse or key event
    std::string type;

    // The button or key pressed
    std::string id;

    // false for up, true for down
    bool isDown;

    int x;
    int y;
};

#endif
