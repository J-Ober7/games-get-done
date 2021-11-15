
#include "SoundFactory.hpp"

SoundFactory::SoundFactory(){}
SoundFactory::~SoundFactory(){}

/**
* Returns a pointer to a new TileMapComponent
*/
SoundComponent* SoundFactory::RequestComponent(const char* filePath){
	
	SoundComponent* sc = new SoundComponent();
	sc->init(filePath);
	m_SoundList.push_back(sc);
	return sc;	
	
}

SoundComponent* SoundFactory::RequestComponent(){
	
	SoundComponent* sc = new SoundComponent();
	m_SoundList.push_back(sc);
	return sc;	
}


/**
* Frees all the Transform components created by the factory from memory
*/
void SoundFactory::DeleteAll(){
	for(int i = 0; i < m_SoundList.size(); i++){
		delete(m_SoundList[i]);
		
	}
}


