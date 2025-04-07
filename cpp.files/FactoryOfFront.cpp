#include "FactoryOfFront.h"

FactoryOfFront::FactoryOfFront(SDL_Renderer* renderer, SDL_Color color, std::string text, int size, const char* filePath)
{
	if (TTF_Init() == -1)
		std::cout << "Couldn't initialize TTF! Error: " << TTF_GetError() << '\n';
	m_text = text;
	m_font = TTF_OpenFont(filePath, size);
	if (!m_font)
		std::cout << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
	SDL_Surface* surface = TTF_RenderText_Solid(m_font, text.c_str(), color);
	if (!surface)
		std::cout << "Failed to load surface! " << SDL_GetError() << std::endl;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
		std::cout << "Failed to load texture! " << SDL_GetError() << std::endl;
	textTexture = texture;
	SDL_FreeSurface(surface);
}

void FactoryOfFront::textToRect(SDL_Rect m_rect)
{
	int textWidth, textHeight;
	TTF_SizeText(m_font, m_text.c_str(), &textWidth, &textHeight);
	SDL_Rect textRect = { m_rect.x + (m_rect.w - textWidth) / 2, m_rect.y + (m_rect.h - textHeight) / 2, textWidth, textHeight };
	m_textRect = textRect;
}



