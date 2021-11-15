#include "GGDProgram.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

// Creates a macro function that will be called
// whenever the module is imported into python
// 'mymodule' is what we 'import' into python.
// 'm' is the interface (creates a py::module object)
//      for which the bindings are created.
//  The magic here is in 'template metaprogramming'
PYBIND11_MODULE(mygameengine, m){
    m.doc() = "our game engine as a library"; // Optional docstring
    
    py::class_<RectWrapper>(m, "Rect")
		.def(py::init<int,int,int,int>(), py::arg("x"), py::arg("y"), py::arg("w"), py::arg("h"))
        .def_readwrite("x",&RectWrapper::x)
        .def_readwrite("y",&RectWrapper::y)
        .def_readwrite("w",&RectWrapper::w)
        .def_readwrite("h",&RectWrapper::h);
		
	py::enum_<CollisionType>(m, "CollisionType")
		.value("Top", CollisionType::Top)
		.value("Bottom", CollisionType::Bottom)
		.value("Left", CollisionType::Left)
		.value("Right", CollisionType::Right)
		.value("NoCollision", CollisionType::NoCollision);

	py::class_<SDL_Rect>(m, "SDL_Rect")
		.def_readwrite("x",&SDL_Rect::x)
		.def_readwrite("y",&SDL_Rect::y)
		.def_readwrite("w",&SDL_Rect::w)
		.def_readwrite("h",&SDL_Rect::h);
		
    py::class_<Collision>(m, "Collision")
		.def(py::init<CollisionType,std::string,int>(), py::arg("type"), py::arg("parentTag"), py::arg("penetration"))
		.def_readwrite("type",&Collision::type)
		.def_readwrite("parentTag",&Collision::parentTag)
		.def_readwrite("penetration",&Collision::penetration);
		
    py::class_<GGDProgram>(m, "GGDProgram")
		.def(py::init<int,int>(), py::arg("w"), py::arg("h"))   // our constructor
		.def("input", &GGDProgram::CheckInput)
		.def("update", &GGDProgram::Update) 
		.def("UpdateCamera", &GGDProgram::UpdateCamera) 
		.def("RenderPresent", &GGDProgram::RenderPresent) 
		.def("RenderClear", &GGDProgram::RenderClear) 
		.def("Shutdown", &GGDProgram::Shutdown)
		.def("closeFrameLimit", &GGDProgram::closeFrameLimit)
		.def("startFrameLimit", &GGDProgram::startFrameLimit)
		.def("delay", &GGDProgram::delay)
		.def("receive", &GGDProgram::receive)
        .def("initializeRendering", &GGDProgram::initializeRendering)
        .def("requestComponent", &GGDProgram::requestComponent)
		.def("Shutdown", &GGDProgram::Shutdown)
		.def("loadJSON", &GGDProgram::loadJSON)
		.def_readwrite("camera",&GGDProgram::camera)
		.def_readwrite("eventLog", &GGDProgram::eventLog);
    
    py::class_<InputEvent>(m, "InputEvent")
		.def(py::init<std::string, std::string, bool, int, int>(), py::arg("type"), py::arg("id"), py::arg("isDown"), py::arg("x"), py::arg("y"))
		.def_readonly("type",&InputEvent::type)
		.def_readonly("id",&InputEvent::id)
		.def_readonly("isDown",&InputEvent::isDown)
		.def_readonly("x",&InputEvent::x)
		.def_readonly("y",&InputEvent::y);

    // COMPONENTS
    py::class_<Component, PyComponent>(m, "Component")
		.def(py::init<>())
		.def("Update", &Component::Update);

    py::class_<SpriteComponent, Component>(m, "SpriteComponent")
        .def("init", static_cast<void (SpriteComponent::*)(int, int, int, int, int, int, int, int, int, int, std::string, float)>(&SpriteComponent::init))
        .def("init", static_cast<void (SpriteComponent::*)(int, int, int, int, int, int, int, int, int, int, std::string)>(&SpriteComponent::init))
		.def("SetFrames", static_cast<void (SpriteComponent::*)(int, int)>(&SpriteComponent::SetFrames))
		.def("SetFrames", static_cast<void (SpriteComponent::*)(std::string)>(&SpriteComponent::SetFrames))
		.def("AddAnimation", &SpriteComponent::AddAnimation)
		.def("SetSpriteOffset", &SpriteComponent::SetSpriteOffset)
		.def("FlipHorizontal", &SpriteComponent::FlipHorizontal)
		.def("FlipVertical", &SpriteComponent::FlipVertical)
		.def_readwrite("animationSpeed", &SpriteComponent::m_animateSpeed);
    
	py::class_<TransformComponent, Component>(m, "TransformComponent");
	
	py::class_<CollisionComponent, Component>(m, "CollisionComponent")
		.def("init", &CollisionComponent::init)
		.def_readwrite("parent", &CollisionComponent::parent)
		.def_readwrite("isMovable", &CollisionComponent::isMovable);
	
	py::class_<PhysicsComponent, Component>(m, "PhysicsComponent")
		.def_readwrite("m_Gravity", &PhysicsComponent::m_Gravity)
		.def_readwrite("m_MaxGravity", &PhysicsComponent::m_MaxGravity)
		.def_readwrite("m_MaxYVel", &PhysicsComponent::m_MaxYVel);
	
	py::class_<SoundComponent, Component>(m, "SoundComponent")
        .def("init", &SoundComponent::init)
		.def("Play", &SoundComponent::Play)
		.def("Pause", &SoundComponent::Pause);
		
	py::class_<TileMapComponent, Component>(m, "TileMapComponent")
        .def("init", static_cast<void (TileMapComponent::*)(std::string, int, int, int,int, int, int, int, int)>(&TileMapComponent::init))
		.def("init", static_cast<void (TileMapComponent::*)(std::string, int, int, int, int, int,int, int, int, float)>(&TileMapComponent::init))
		.def("addCollidableTile", &TileMapComponent::addCollidableTile)
		.def("SetTile", &TileMapComponent::SetTile)
		.def("GetTileType", &TileMapComponent::GetTileType)
		.def_readwrite("background", &TileMapComponent::background)
		.def_readwrite("parallax", &TileMapComponent::parallax)
		.def_readwrite("m_MapX", &TileMapComponent::m_MapX)
		.def_readwrite("m_MapY", &TileMapComponent::m_MapY)
		.def_readwrite("m_TileWidth", &TileMapComponent::m_TileWidth)
		.def_readwrite("m_TileHeight", &TileMapComponent::m_TileHeight)
		.def_readwrite("debug", &TileMapComponent::debug);
		
	
    py::class_<GameObject>(m, "GameObject")
        .def(py::init<>())
		//.def(py::init<int,int,int,int,int>(), py::arg("x"), py::arg("y"), py::arg("w"), py::arg("h"), py::arg("xv"), py::arg("yv"))
		//.def(py::init<int,int,int,int,int,std::string &>(), py::arg("x"), py::arg("y"), py::arg("w"), py::arg("h"), py::arg("xv"), py::arg("yv"), py::arg("tag")) // our constructor
		.def("AddComponent", static_cast<void (GameObject::*)(Component*)>(&GameObject::AddComponent))      // Expose member methods
        // cast overloaded methods to function pointers
        .def("init", static_cast<void (GameObject::*)(int,int,int,int,int,int)>(&GameObject::init))
        .def("init", static_cast<void (GameObject::*)(int,int,int,int,int,int,std::string)>(&GameObject::init))
		.def("update", &GameObject::Update)
		.def("render", &GameObject::Render)      
		.def("SetPosition", &GameObject::SetPosition)
		.def("SetDimensions", &GameObject::SetDimensions)
		.def("SetVelocity", &GameObject::SetVelocity)
		.def("SetAcceleration", &GameObject::SetAcceleration)
		.def("GetXPosition", &GameObject::GetXPosition)
		.def("GetYPosition", &GameObject::GetYPosition)
		.def("clearCollisions", &GameObject::clearCollisions)
		.def_readwrite("collisions", &GameObject::collisions)
        .def_readwrite("m_xVel", &GameObject::m_xVel)
        .def_readwrite("m_yVel", &GameObject::m_yVel)
        .def_readwrite("m_xAcel", &GameObject::m_xAcel)
        .def_readwrite("m_yAcel", &GameObject::m_yAcel)
        .def_readwrite("m_tag", &GameObject::m_tag)
        .def_readwrite("isGrounded", &GameObject::isGrounded)
		.def_readwrite("position", &GameObject::position)
		.def_readwrite("isActive", &GameObject::isActive)
		.def_readwrite("debug", &GameObject::debug);     
}