#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <unordered_map>
#include <thread>
#include <future>
#include <tuple>
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
	Editor() = default;
	Editor(App* app, SDL_Renderer* renderer);
	~Editor() {
		delete ptrToImplForRenderer;
		delete menuForRenderer;
	}

	void freezeBlock(SDL_Renderer* renderer, App* app);
	void chooseBlock(SDL_Renderer* renderer);
	void deleteBlock(SDL_Renderer* renderer, App* app);
	void clearAll(SDL_Renderer* renderer) { ptrToImpl->lastEl.clear(); }

	//void render(SDL_Renderer* renderer);
	//void renderBackground(SDL_Renderer* renderer);

	void HandleActions(int& number, SDL_Renderer* renderer, App* app);

private:
	void keeperBlock(int number, SDL_Renderer* renderer);

	struct impl {
		int size = 0;
		bool number_b = 1;
		bool m_forChoose = 0;
		bool menuForEditor = 0;
		bool blockFrozen;
		std::unordered_map<char, uint8_t> rgbColors{ {'r',0},{'g',0},{'b',0},{'a',0} };
		std::multimap<std::string, int> lastEl;
		std::vector<int> numbers;
		std::vector<std::unique_ptr<FactoryOfRect>> m_factGrass;
		std::vector<std::unique_ptr<FactoryOfRect>> m_factTrees;
		std::vector<std::unique_ptr<FactoryOfRect>> m_factLeaf;
		std::vector<std::unique_ptr<FactoryOfRect>> m_factEmpty;
		std::vector<std::unique_ptr<FactoryOfFront>> m_factFront;
	};
	std::unique_ptr<impl> ptrToImpl;
	std::unique_ptr<MenuForEditor> menu;

protected:
	static impl* ptrToImplForRenderer;
	static MenuForEditor* menuForRenderer;

	friend class Renderer;
};

