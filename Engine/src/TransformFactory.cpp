
#include "TransformFactory.hpp"

TransformFactory::TransformFactory(){}
TransformFactory::~TransformFactory(){}

/**
* Returns a pointer to a new TileMapComponent
*/
TransformComponent* TransformFactory::RequestComponent(){
	
	TransformComponent* tc = new TransformComponent();
	//tc->init();
	m_TransformList.push_back(tc);
	return tc;	
	
}


/**
* Frees all the Transform components created by the factory from memory
*/
void TransformFactory::DeleteAll(){
	for(int i = 0; i < m_TransformList.size(); i++){
		delete(m_TransformList[i]);
		
	}
}


