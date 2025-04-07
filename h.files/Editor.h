#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include "FactoryOfRect.h"
#include "ActionsOfRect.h"
#include "FactoryOfFront.h"
#include "App.h"

import MenuForEditor;

class Editor
{
public:
	Editor(App* app, SDL_Renderer* renderer);
	~Editor() = default;

	void freezeBlock(SDL_Renderer* renderer, App* app);
	void chooseBlock(SDL_Renderer* renderer);
	void deleteBlock(SDL_Renderer* renderer, App* app);
	void clearAll(SDL_Renderer* renderer) { lastEl.clear(); }
	
	void render(SDL_Renderer* renderer);
	
	void forApp(int& number, SDL_Renderer* renderer, App* app);

	//bool getChoose() { return m_forChoose; }
	//std::vector<std::unique_ptr<FactoryOfRect>> getFactGrass() { return m_factGrass; }
	//std::vector<std::unique_ptr<FactoryOfRect>> getFactTrees() { return m_factTrees; }
	//std::vector<std::unique_ptr<FactoryOfRect>> getFactLeaf() { return m_factLeaf; }
	//std::vector<std::unique_ptr<FactoryOfFront>> getFactFront() { return m_factFront; }

private:
	void keeperBlock(int number, SDL_Renderer* renderer);

	int size;
	bool number_b;
	bool m_forChoose; 
	bool menuForEditor;
	std::multimap<std::string, int> lastEl;
	std::vector<int> numbers;
	std::vector<std::unique_ptr<FactoryOfRect>> m_factGrass;
	std::vector<std::unique_ptr<FactoryOfRect>> m_factTrees;
	std::vector<std::unique_ptr<FactoryOfRect>> m_factLeaf;
	std::vector<std::unique_ptr<FactoryOfRect>> m_factEmpty;
	std::vector<std::unique_ptr<FactoryOfFront>> m_factFront;
	MenuForEditor menu;
};
