#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class MemoryManager
{
public:

	static MemoryManager& getInstance();

	SDL_Surface* load(std::string filepath);

	void history();

private:
	MemoryManager() = default;
	MemoryManager(const MemoryManager&) = delete;
	MemoryManager operator=(const MemoryManager&) = delete;
	std::unordered_map<std::string, SDL_Surface*> m_surfaces;
};

