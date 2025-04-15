#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>
#include <SDL.h>
#include "Editor.h"
#include "Menu.h"
#include "App.h"

import Renderer;

enum class Type{MAIN_GAME,MAIN_EDITOR,MAIN_SETTINGS,MAIN_EXIT,MAIN_MENU};

class outro
{
public:
	outro()
	{
		pImpl = std::make_unique<Impl>();
	}
	~outro() {
		delete pImpl->app;
		delete pImpl->renderer;
	}

	// can embrace only lambdas (ofc you can also leave here
	// a function, but why u need to create this if lambdas
	// are a much more flex?)
	//MAIN_GAME / MAIN_EDITOR / MAIN_SETTINGS / MAIN_EXIT / MAIN_MENU
	void appendFunctional(Type type,std::function<void(void)> func);
	//MAIN_GAME / MAIN_EDITOR / MAIN_SETTINGS / MAIN_EXIT / MAIN_MENU
	void manageFunctional(int& number);
	
	int getNumberFromMenu() { return pImpl->number; }

private:
	struct Impl {
		int number = 0;
		std::unordered_map<Type, std::function<void(void)>> mapOfFunctions;
	};
	std::unique_ptr<Impl> pImpl;
};

