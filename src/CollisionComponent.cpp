#include "CollisionComponent.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL.h>
#endif
#include <iostream>

CollisionComponent::CollisionComponent() {}

CollisionComponent::~CollisionComponent() {}

void CollisionComponent::init(GameObject* gameObject){
	parent = gameObject;
}

void CollisionComponent::Update(GameObject &gameObject)
{
    collider = parent->position;
}

void CollisionComponent::SetColliderSize(int width, int height) {
    collider.w = width;
    collider.h = height;
}

void CollisionComponent::Render(SDL_Renderer* ren) {
    //SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
    //SDL_RenderDrawRect(ren, &parent->position);
}

Collision *CollisionComponent::CheckCollision(CollisionComponent &other)
{
    collider = parent->position;

    /*collider.x = parent->position.x;
    collider.y = parent->position.y;*/
    Collision *contact = new Collision{CollisionType::NoCollision, other.parent->m_tag, 0};

    // TODO: if we are calculating future positions, we'd need to also calculate the future position of the other colliders

    // top left corner: collider->gameObject->position.x, position.y
    // top right corner: collider->gameobject->position.x + position.w, position.y
    // bottom left corner: collider->gameObject->position.x, position.y + position.h
    // bottom right corner: collider->gameObject->position.x + position.w, position.y + position.h
    int leftX = collider.x ;//+ parent->m_xVel;
    int rightX = leftX + collider.w;
    int topY = collider.y;// + parent->m_yVel;
    int bottomY = topY + collider.h;

    int otherLeftX = other.parent->position.x;// + other.parent->m_xVel;
    int otherRightX = otherLeftX + other.parent->position.w;
    int otherTopY = other.parent->position.y;// + other.parent->m_yVel;
    int otherBottomY = otherTopY + other.parent->position.h;

    float centerX = leftX + 0.5f * collider.w;
    float centerY = topY + 0.5f * collider.h;

    float otherCenterX = otherLeftX + 0.5f * other.parent->position.w;
    float otherCenterY = otherTopY + 0.5f * other.parent->position.h;

    if (leftX >= otherRightX || rightX <= otherLeftX || topY >= otherBottomY || bottomY <= otherTopY)
    {
        return contact;
    }

    int ymin = otherTopY > topY ? otherTopY : topY;
    int ymax = otherBottomY < bottomY ? otherBottomY : bottomY;
    int ysize = ymax - ymin;

    int xmin = otherLeftX > leftX ? otherLeftX : leftX;
    int xmax = otherRightX < rightX ? otherRightX : rightX;
    int xsize = xmax - xmin;

    std::cout << " x size " << xsize << " y size " << ysize << std::endl;

    if (xsize > ysize)
    {
        contact->penetration = ysize;
        //Bottom Collision
        if (centerY > otherCenterY)
        {
            //SDL_Log("BOTTOM");
            contact->type = CollisionType::Bottom;
        }
        else
        {
            //Top Collision
            contact->type = CollisionType::Top;
        }
    }
    else
    {
        contact->penetration = xsize;
        //Left Collision
        if (centerX > otherCenterX)
        {
            //SDL_Log("BOTTOM");
            contact->type = CollisionType::Left;
        }
        else
        {
            //Right Collision
            contact->type = CollisionType::Right;
        }
    }
    std::cout << "penetration: " << contact->penetration << std::endl;
    return contact;
}

// DEPRECATED
void CollisionComponent::HandleCollision()
{
	//printf("%i  %i\n", parent->position.x, parent->position.y);
    // if this collision component
    if (isMovable && parent != nullptr)
    {
		
		int maxLeftPen = 0;
		int maxRightPen = 0;
		int maxTopPen = 0;
		int maxBotPen = 0;
		parent->isGrounded = false;
		int numCollisions = parent->collisions.size();
		for(int i = 0; i < numCollisions; i++){
			Collision* col = parent->collisions[i];
			// this operates under the assumption the parent game object has already been moved
			// TODO potential problem here is that we might end up moving both objects during the collision
			// or that if both objects are moving towards each other, only one of the objects ends up reacting,
			// and therefore gets pushed back too far with the penetration value (fix: use the min of the velocity and the penetration)
			if (col->type == CollisionType::Bottom)
			{
				parent->m_yVel = 0;
				if (col->penetration > maxBotPen){
					maxBotPen = col->penetration;
				}
			}
			else if (col->type == CollisionType::Top)
			{
				parent->m_yVel = 0;
				parent->m_yAcel = 0;
				parent->isGrounded = true;
				if (col->penetration > maxTopPen){
					maxTopPen= col->penetration;
				}
			}
			else if (col->type == CollisionType::Left)
			{
				parent->m_xVel = 0;
				if (col->penetration > maxLeftPen){
					maxLeftPen= col->penetration;
				}
			}
			else if (col->type == CollisionType::Right)
			{
				parent->m_xVel = 0;
				if (col->penetration > maxRightPen){
					maxRightPen= col->penetration;
				}
			}
		}
		parent->position.x += maxLeftPen;
		parent->position.x -= maxRightPen;
		parent->position.y -= maxTopPen;
		parent->position.y += maxBotPen;
    }
}
