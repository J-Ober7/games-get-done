#include "PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(){
}

PhysicsComponent::~PhysicsComponent(){
}

//Apply velocity to position

void PhysicsComponent::Update(GameObject & gameObject){
	
	
	//Gravity (only apply if player is not grounded)
	/*if(gameObject.m_yAcel > m_MaxGravity && !gameObject.isGrounded){
		gameObject.m_yAcel += m_Gravity;
	}*/
	if (gameObject.m_yVel > m_MaxYVel){
		gameObject.m_yVel += gameObject.m_yAcel;
	}
	if(!gameObject.isGrounded){
		gameObject.m_yVel += m_Gravity;
	}
	
	

	gameObject.m_xVel += gameObject.m_xAcel;
	

	// move
	gameObject.position.x += gameObject.m_xVel;
	gameObject.position.y -= gameObject.m_yVel;
}