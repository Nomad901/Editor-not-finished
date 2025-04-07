#include "FactoryOfRect.h"


FactoryOfRect::FactoryOfRect(SDL_Renderer* renderer)
	: m_texture(nullptr)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, SDL_ALPHA_OPAQUE);
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = 32;
	m_rect.h = 32;
}

FactoryOfRect::FactoryOfRect(SDL_Renderer* renderer, const char* filePath)
{
	SDL_Surface* retrieveSurface = MemoryManager::getInstance().load(filePath);
	m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);
	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = 32;
	m_rect.h = 32;
}

void FactoryOfRect::setProperties(const int w, const int h)
{
	m_rect.w = w;
	m_rect.h = h;
}

void FactoryOfRect::setPosition(const int x, const int y) 
{
	m_rect.x = x;
	m_rect.y = y;
}

SDL_bool FactoryOfRect::mouseInRect(int mouseX, int mouseY)
{
	return static_cast<SDL_bool>((mouseX > m_rect.x && (mouseX < m_rect.x + m_rect.w)
							   && mouseY > m_rect.y && (mouseY < m_rect.y + m_rect.h)));
}







