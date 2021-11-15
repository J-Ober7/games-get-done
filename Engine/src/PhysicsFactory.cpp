
#include "PhysicsFactory.hpp"

PhysicsFactory::PhysicsFactory(){}
PhysicsFactory::~PhysicsFactory(){}

/**
* Returns a pointer to a new TileMapComponent
*/
PhysicsComponent* PhysicsFactory::RequestComponent(){
	
	PhysicsComponent* pc = new PhysicsComponent();
	//tc->init();
	m_PhysicsList.push_back(pc);
	return pc;	
	
}


/**
* Frees all the Transform components created by the factory from memory
*/
void PhysicsFactory::DeleteAll(){
	for(int i = 0; i < m_PhysicsList.size(); i++){
		delete(m_PhysicsList[i]);
		
	}
}


