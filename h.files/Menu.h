#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "SDL.h"
#include "SDL_image.h"
#include "App.h"
#include "FactoryOfRect.h"
#include "FactoryOfFront.h"

class Menu
{
public:

	static Menu& getInstance();

	void background(SDL_Window* window, SDL_Renderer* renderer);
	int buttons(SDL_Renderer* renderer);

private:
	Menu();
	~Menu() { 
		delete p;
		m_smrtVct.clear();
		m_textVct.clear();
		TTF_Quit();
		SDL_Quit();
	}

	int mouseX, mouseY;
	std::vector<std::unique_ptr<FactoryOfRect>> m_smrtVct;
	std::vector<std::unique_ptr<FactoryOfFront>> m_textVct;
	SDL_Renderer* m_renderer;
	App* p;
};

