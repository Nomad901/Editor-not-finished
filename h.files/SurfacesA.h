#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include "FactoryOfRect.h"

class SurfacesA
{
public:
	SurfacesA(SDL_Renderer* renderer);
	~SurfacesA() = default;

	void generation(SDL_Renderer* renderer);

private:
	void trees(SDL_Renderer* renderer, int x, int y);
	void grass(SDL_Renderer* renderer);
	std::vector<std::unique_ptr<FactoryOfRect>> m_factGrass;
	std::vector<std::unique_ptr<FactoryOfRect>> m_factTrees;
};

