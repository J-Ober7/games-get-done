#include "TransformComponent.hpp"
#include <iostream>

TransformComponent::TransformComponent(){
}

TransformComponent::~TransformComponent(){
}

//Apply velocity to position

void TransformComponent::Update(GameObject & gameObject){
	/*int maxLeftPen = 0;
	int maxRightPen = 0;
	int maxTopPen = 0;
	int maxBotPen = 0;

	for (int i = 0; i < gameObject.collisions.size(); i++) {
		Collision c = *(gameObject.collisions[i]);
		if (c.type == CollisionType::Left) {
			if(c.penetration > maxLeftPen){
				maxLeftPen= c.penetration;
			}
			//gameObject.m_xVel = 0;
		}
		else if (c.type == CollisionType::Right) {
			if(c.penetration > maxRightPen){
				maxRightPen= c.penetration;
			}
			//gameObject.m_xVel = 0;
		} 
		else if (c.type == CollisionType::Top) {
			if(c.penetration > maxTopPen){
				maxTopPen = c.penetration;
			}
			gameObject.m_yVel = 0;
			gameObject.canJump = true;
		} 
		else if (c.type == CollisionType::Bottom) {
			if(c.penetration > maxBotPen){
				maxBotPen = c.penetration;
			}
			gameObject.m_yVel = 0;
		}
	}
	//std::cout << "total collisions " << gameObject.collisions.size() << " left pen " << maxLeftPen << " right pen " << maxRightPen << " top pen " << maxTopPen << " bottom pen " << maxBotPen << std::endl;
	gameObject.position.x += maxLeftPen;
	gameObject.position.x -= maxRightPen;
	gameObject.position.y -= maxTopPen;
	gameObject.position.y += maxBotPen;*/
	/*gameObject.position.x += gameObject.m_xVel;
	gameObject.position.y -= gameObject.m_yVel;*/
}