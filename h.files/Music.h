#pragma once
#include <iostream>
#include <SDL/SDL_mixer.h>

//TODO: IN THE FUTURE I CAN CHOOSE MUSIC IN THE MENU


enum class type{MP3, WAV};

class Music
{
public:
	Music(std::string musicPath);
	~Music();

	// loops - -1 your music will be playing endlessly
	// 0 your music wont be playing
	void playMusic(int loops);
	void stopMusic();

	//0 - 128 volume
	void setVolume(int volume);

private:
	Mix_Music* music;
};

