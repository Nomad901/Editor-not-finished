#include "Music.h"

Music::Music(std::string musicPath)
	: music(nullptr)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == 1) {
		std::cout << "Mix_OpenAudio is not working: " << Mix_GetError();
	}

	music = Mix_LoadMUS(musicPath.c_str());
	if (!music)
		std::cout << "Couldnt download the music path!" << '\n';
}

Music::~Music()
{
	Mix_FreeMusic(music);
	Mix_CloseAudio();
}

void Music::playMusic(int loops)
{
	if (music != nullptr)
		Mix_PlayMusic(music, loops);
}

void Music::stopMusic()
{
	Mix_PauseMusic();	
}

void Music::setVolume(int volume)
{
	Mix_VolumeMusic(volume);
}
