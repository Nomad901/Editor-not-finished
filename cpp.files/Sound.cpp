#include "Sound.h"

Sound::Sound(std::string filepath)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == 1)
		std::cout << "Couldnt initialize sounds: " << Mix_GetError();
	m_sound = Mix_LoadWAV("E:/Hit_Hurt2.wav");
	if (!m_sound)
		std::cout << "Couldnt initialize path of your sound!\n";
}

Sound::~Sound()
{
	Mix_FreeChunk(m_sound);
	Mix_CloseAudio();
}

void Sound::playSound()
{
	Mix_PlayChannel(-1, m_sound, 0);
}

void Sound::setVolume(int volume)
{
	Mix_VolumeChunk(m_sound, volume);
}


