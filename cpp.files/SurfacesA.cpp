#include "SurfacesA.h"

SurfacesA::SurfacesA(SDL_Renderer* renderer)
{
	grass(renderer);
	trees(renderer,300,520);
}

void SurfacesA::generation(SDL_Renderer* renderer)
{

}

void SurfacesA::trees(SDL_Renderer* renderer, int x, int y)
{
	

}

void SurfacesA::grass(SDL_Renderer* renderer)
{
	int number = 0;
	for (int i = 0; i < 15; i++)
	{
		m_factGrass.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/grass.png"));
	}
	for (auto& i : m_factGrass)
	{
		i->setPosition(number, 620);
		number += 100;
		i->render(renderer);
	}
}


