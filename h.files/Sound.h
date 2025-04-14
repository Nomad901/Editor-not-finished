#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL/SDL_mixer.h>

class ISound { // extendable 
public:
	virtual ~ISound() {};
	
	virtual void playSound() = 0;
	//virtual void stopSound() = 0;
	virtual void setVolume(int volume) = 0;
};

class Sound : public ISound
{
public:
	
	Sound(std::string filepath);
	~Sound();

	void playSound() override;
	//void stopSound() override;
	void setVolume(int volume) override;

private:
	Mix_Chunk* m_sound;
};


