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

enum class Type { MAIN_MENU, MAIN_GAME, MAIN_EDITOR, MAIN_SETTINGS, MAIN_EXIT };

class outro
{
public:
	outro() : number(0){}
	~outro(){}
	
	//MAIN_GAME, MAIN_EDITOR, MAIN_SETTINGS, MAIN_EXIT, MAIN_MENU
	void appendFunction(Type type, std::function<void(void)> func) {	
		auto it = mapOfLambdas.find(type);
		if (it != mapOfLambdas.end())
			mapOfLambdas[type] = std::function<void(void)>(func);
		else
			mapOfLambdas.emplace(std::make_pair(type, std::function<void(void)>(func)));
	}
	void appendMenu(std::function<int(void)> func) {
			mainMenu = func;
	}

	void removeFunction(Type type) {
		auto it = mapOfLambdas.find(type);
		if (it != mapOfLambdas.end())
			mapOfLambdas.erase(it);
		else
			std::cout << "this type doesnt exist!\n";
	}
	void removeAll() {
		mapOfLambdas.clear();
	}

	void execute(Type type) {
		if (type == Type::MAIN_MENU)
			number = mainMenu();
		else {
			if (lastType.back() != type) {
				auto it = mapOfLambdas.find(type);
				if (it != mapOfLambdas.end())
				{
					it->second();
					lastType.push_back(type);
				}
			}
			else {
				auto it = mapOfLambdas.end();
				it->second();
			}
		}
	}
	void executeOfNumber() {
		execute(static_cast<Type>(number));
	}

	int& getNumber() { return number; }

private:
	std::unordered_map<Type, std::function<void(void)>> mapOfLambdas;
	std::function<int(void)> mainMenu;
	std::vector<Type> lastType;
	int number;
};

