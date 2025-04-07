#include "MemoryManager.h"

MemoryManager& MemoryManager::getInstance()
{
	static MemoryManager instance;
	return instance;
}

SDL_Surface* MemoryManager::load(std::string filepath)
{
	auto search = m_surfaces.find(filepath);
	if (search != m_surfaces.end())
		return m_surfaces[filepath];
	else {
		SDL_Surface* surface = IMG_Load(filepath.c_str());
		if (!surface)
			std::cout << "Couldnt initialize the picture!\n";
		m_surfaces.insert(std::make_pair(filepath, surface));

		return m_surfaces[filepath];
	}
	return nullptr;

}


void MemoryManager::history()
{
	for (auto& i : m_surfaces)
	{
		std::cout << i.first << " , "<<i.second<<'\n';
	}
}
