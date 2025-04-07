#pragma once
#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class FactoryOfFront
{
public:
	FactoryOfFront(SDL_Renderer* renderer, SDL_Color color, std::string text, int size, const char* filePath);
	~FactoryOfFront() {
		SDL_DestroyTexture(textTexture);
		TTF_CloseFont(m_font);
	}

	void textToRect(SDL_Rect m_rect);

	void render(SDL_Renderer* renderer) {
		SDL_RenderCopy(renderer, textTexture, NULL, &m_textRect);
	}

private:
	TTF_Font* m_font;
	SDL_Texture* textTexture;
	SDL_Rect m_textRect;
	std::string m_text;
};

