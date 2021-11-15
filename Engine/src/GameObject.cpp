#include "GameObject.hpp"
#include <typeinfo>

GameObject::GameObject(){
	init(0,0,0,0,0,0);
}

GameObject::~GameObject(){
}

void GameObject::init(int x, int y, int w, int h, int xv, int yv){
	init(x, y, w, h, xv, yv, "none");
}

void GameObject::init(int x, int y, int w, int h, int xv, int yv, std::string tag){
	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
	m_xVel = xv;
	m_yVel = yv;
	m_tag = tag;
}

void GameObject::AddComponent(Component* comp){
	comp->parent = this;
	m_components.push_back(comp);
}

void GameObject::Render(){
	if (isActive) {
		size_t size = m_components.size();
		for(size_t i = 0; i < size; i++){
			m_components.at(i)->Render(m_renderer);
		}
	}
}


void GameObject::Update(){
	if (isActive) {
		size_t size = m_components.size();
		for(size_t i = 0; i < size; i++){
			m_components.at(i)->Update(*this);
		}
	}
}


void GameObject::GiveSDLEvents(std::vector<SDL_Event> *events){
	sdlEventLog = events;
}


void GameObject::SetPosition(int x, int y){
	position.x = x;
	position.y = y;
}
		
void GameObject::SetDimensions (int w, int h){
	position.w = w;
	position.h = h;
	
}
		
void GameObject::SetVelocity (int x, int y){
	m_xVel = x;
	m_yVel = y;
	
}
		
void GameObject::SetAcceleration(int x, int y){
	m_xAcel = x;
	m_yAcel = y;
	
}

void GameObject::SetRenderer(SDL_Renderer* renderer) {
	m_renderer = renderer;
}

void GameObject::AddComponent(std::string key,Component* comp) {
	m_components_map.insert(std::pair<std::string, Component*>(key, comp));  
}

Component* GameObject::GetComponentMap(std::string key){
	return m_components_map.at(key);
}

int GameObject::GetXPosition(){
	return position.x;
}
int GameObject::GetYPosition(){
	return position.y;
}

void GameObject::clearCollisions(){
	for (int i = 0; i < collisions.size(); i++) {
		delete collisions[i];
		collisions[i] = nullptr;
	}
	collisions.clear();
}