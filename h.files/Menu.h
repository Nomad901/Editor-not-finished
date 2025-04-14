#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "App.h"
#include "FactoryOfRect.h"
#include "FactoryOfFront.h"

class Menu
{
public:

	static Menu& getInstance();

	void background(SDL_Window* window, SDL_Renderer* renderer, std::string backgroundPath);
	int buttons(SDL_Renderer* renderer);

private:
	Menu();
	~Menu() { 
		TTF_Quit();
		SDL_Quit();
	}

	struct impl {
		int mouseX = 0;
		int mouseY = 0;
		std::vector<std::unique_ptr<FactoryOfRect>> m_smrtVct;
		std::vector<std::unique_ptr<FactoryOfFront>> m_textVct;
		SDL_Renderer* m_renderer;
	};	

	std::unique_ptr<impl> pImpl;
protected:
	static impl* pImplForRenderer;
	friend class Renderer;
};

