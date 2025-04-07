#pragma once
#include <iostream>
#include <print>
#include <vector>
#include <memory>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "MemoryManager.h"

class FactoryOfRect
{
public:
	FactoryOfRect(SDL_Renderer* renderer);
	FactoryOfRect(SDL_Renderer* renderer, const char* filePath);
	~FactoryOfRect() {
		if (m_texture) {
			SDL_DestroyTexture(m_texture);
		}
	}
	
	void setProperties(const int w, const int h);
	void setPosition(const int x,const int y);
	
	SDL_bool mouseInRect(int mouseX, int mouseY);


	void render(SDL_Renderer* renderer) const {
		SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
	}

	inline SDL_Rect getRect() const {
		return m_rect;
	}
	

private:
	SDL_Rect m_rect;
	SDL_Texture* m_texture;

};

