#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include <vector>
#include <string>
#include <map>

/**
 * @brief Represents the various tags that a game object can hold for identification.
 */
enum Tag {
    None,
    Player,
    Enemy
};

class Component;
struct Collision;
#include "Component.hpp"



/**
 * @brief This class represents a basic object in the game.
 */
class GameObject{
    public:
        /**
         * @brief Constructs a GameObject
         */
        GameObject(); //expose

        /**
         * @brief Destructs a GameObject
         */
        ~GameObject();

        /**
         * @brief Initializes member fields of GameObject
         * x and y is the world position (x, y). Indicates the top left corner of the object
         * w and h is object width and height
         * xv and yv is the velocity (xv, yv) 
         */
		void init(int x, int y, int w, int h, int xv, int yv); //expose

        /**
         * @brief Initializes member fields of GameObject
         * x and y is the world position (x, y). Indicates the top left corner of the object
         * w and h is object width and height
         * xv and yv is the velocity (xv, yv) 
         * tag is the tag given to this GameObject
         */
		void init(int x, int y, int w, int h, int xv, int yv, std::string tag);

        /**
         * @brief Adds a component to the game object
         */
		void AddComponent(Component* comp); //Expose
		
		
		void AddComponent(std::string key,Component* comp);
		
		Component* GetComponentMap(std::string key);

        /**
         * @brief Renders the game object each frame
         */
		void Render(); //expose

        /**
         * @brief Updates the state of the game object each frame
         */
		void Update(); //expose

        /**
         * @brief Gives the object access to the input events
         */
		void GiveSDLEvents(std::vector<SDL_Event> *events); //Delete?

        /**
         * @brief Vector contains the SDL events for this frame
         */
        std::vector<SDL_Event> *sdlEventLog; // Delete?
		
		void SetPosition(int x, int y);
		
		void SetDimensions (int w, int h);
		
		void SetVelocity (int x, int y);
		
		void SetAcceleration(int x, int y);

        void SetRenderer(SDL_Renderer* renderer);
		
		int GetXPosition();
		
		int GetYPosition();

        void clearCollisions();

        /**
         * @brief position holds (x, y) world position, w width, and h height
         */
		SDL_Rect position;

        /**
         * @brief (m_xVel, m_yVel) is the velocity of the object
         */
		int m_xVel, m_yVel;
		
		int m_xAcel{0};
		int m_yAcel{0};
        
        // Tag of this gameobject (for identification purposes)
        std::string m_tag;

        /**
         * @brief Can the object jump?
         */
        bool isGrounded{true}; //delete?

        /**
         * @brief A list of all the current collision events for this GameObject. Accessible to all components.
         */
        std::vector<Collision*> collisions; //Not quite sure how we are handling this

        /**
         * @brief Is this gameobject currently in the scene
         * 
         */
        bool isActive{true};

        /**
         * @brief Is debug mode on for this game object?
         * 
         */
        bool debug{false};
		
    private:
        /**
         * @brief Vector contains all the components of the gameObject
         */
        std::vector<Component*> m_components;// convert to map?
		std::map<std::string, Component*> m_components_map;

        SDL_Renderer* m_renderer;
};


/*#include <pybind11/pybind11.h>
namespace py = pybind11;


PYBIND11_MODULE(mymodule, m){
    m.doc() = "our GameObject as a library"; // Optional docstring

    py::class_<GameObject>(m, "GameObject")
            .def(py::init<int,int,int,int,int>(), py::arg("x"), py::arg("y"), py::arg("w"), py::arg("h"), py::arg("xv"), py::arg("yv"))
			.def(py::init<int,int,int,int,int,std::string &>(), py::arg("x"), py::arg("y"), py::arg("w"), py::arg("h"), py::arg("xv"), py::arg("yv"), py:arg("tag")) // our constructor
            .def("AddComponent", &GameObject::AddComponent)      // Expose member methods
            .def("update", &GameObject::Update)
            .def("render", &GameObject::Render)      
            .def("SetPosition", &GameObject::SetPosition)
            .def("SetDimensions", &GameObject::SetDimensions)
            .def("SetVelocity", &GameObject::SetVelocity)
            .def("SetAcceleration", &GameObject::SetAcceleration)
            .def_readwrite("collisions", &GameObject::collision)
}*/


#endif



