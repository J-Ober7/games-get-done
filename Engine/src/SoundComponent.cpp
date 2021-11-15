#include "SoundComponent.hpp"

SoundComponent::SoundComponent(){}

SoundComponent::~SoundComponent(){
    Mix_FreeMusic(music);
}

void SoundComponent::init(const char* filePath){
	// Load music
	music = Mix_LoadMUS(filePath);
	if (music == NULL) {
		//SDL_Log(Mix_GetError());
	}
	else {
		// Start music (loops forever)
		Mix_PlayMusic(music, -1);
		Mix_VolumeMusic(10);
	}
	
}



void SoundComponent::Update(GameObject & gameObject)
{
	
}

void SoundComponent::Play(){
	if(Mix_PlayingMusic() == 0){
		Mix_PlayMusic(music, -1);
	}else{
		Mix_ResumeMusic();
	}
}

void SoundComponent::Pause(){
	if(Mix_PlayingMusic() == 1){
		Mix_PauseMusic();
	}
}