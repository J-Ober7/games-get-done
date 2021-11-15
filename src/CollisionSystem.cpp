#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem() {

}

CollisionSystem::~CollisionSystem() {

}

void CollisionSystem::init(TileMapFactory* factory) {
    tmf = factory;
}

void CollisionSystem::shutDown() {
    for (int i = 0; i < GameColliders.size(); i++) {
        delete GameColliders[i];
        GameColliders[i] = NULL;
    }
}

CollisionComponent* CollisionSystem::RequestComponent() {
    CollisionComponent* col = new CollisionComponent();
    GameColliders.push_back(col);
    return col;
}

CollisionType getInverseCollision(CollisionType c) {
    switch(c) {
        case CollisionType::Top:
            return CollisionType::Bottom;
        case CollisionType::Bottom:
            return CollisionType::Top;
        case CollisionType::Left:
            return CollisionType::Right;
        case CollisionType::Right:
            return CollisionType::Left;
        default:
            return c;
    }
} 

void CollisionSystem::checkCollisions() {
    Collision* col;
    Collision* inverseCol;
    for (int i = 0; i < GameColliders.size(); i++) {
        CollisionComponent* first = GameColliders[i];

        if (first->parent->isActive) {
            // check against other colliders
            for (int j = i +1; j < GameColliders.size(); j++) {
                if (GameColliders[j]->parent->isActive) {
                    col = first->CheckCollision(*GameColliders[j]);
                    first->parent->collisions.push_back(col);
                    //std::cout << "collision system: collider penetration " << col->penetration << std::endl;
                    // get the inverse of this collision
                    inverseCol = new Collision{getInverseCollision(col->type), first->parent->m_tag, col->penetration};
                    GameColliders[j]->parent->collisions.push_back(inverseCol);
                }
            }

            // check against the tile maps
            for (int k = 0; k < tmf->m_tileMaps.size(); k++) {
                tmf->m_tileMaps[k]->CheckCollsion(first);
                //printf ("%i ", k );
            }
            //printf("\n");
        }
    }
	
	//printf("%i \n", tmf->m_tileMaps.size());
}

void CollisionSystem::handleCollisions() {
    Collision* col;
    Collision* inverseCol;
    for (int i = 0; i < GameColliders.size(); i++) {
        GameColliders[i]->HandleCollision();
		//printf("%i \n", i);
    }
}