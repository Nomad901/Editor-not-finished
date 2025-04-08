
export module MenuForEditor;

import <iostream>;
import <vector>;
import <memory>;
import <string>;
import <SDL.h>;
import <SDL_image.h>;
import "FactoryOfFront.h";
import "FactoryOfRect.h";
import "App.h";

export class MenuForEditor {
public:
	MenuForEditor(App* app, SDL_Renderer* renderer);
	~MenuForEditor() {
		fctOfFront.clear();
		fctOfEmpty.clear();
	};

	void handleRender(SDL_Renderer* renderer);

private:
	std::vector<std::unique_ptr<FactoryOfFront>> fctOfFront;
	std::vector<std::unique_ptr<FactoryOfRect>> fctOfEmpty;
};


MenuForEditor::MenuForEditor(App* app, SDL_Renderer* renderer)
{
	auto helperForOne = [&](int positionX, std::string text) 
	{
		SDL_Color white{ 255,255,255,255 };
		fctOfFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, text, 16, "E:/Arial.ttf"));
		fctOfEmpty.push_back(std::make_unique<FactoryOfRect>(renderer));
		static int number = 0;
		fctOfEmpty[fctOfEmpty.size()-1]->setProperties(50, 50);
		fctOfEmpty[fctOfEmpty.size()-1]->setPosition(positionX, number);
		number += 50;
	};
	auto helperForMultiple = [&](int positionX, std::vector<std::string> texts)
		{
			SDL_Color white{ 255,255,255,255 };
			
			size_t sizeOfFront = fctOfFront.size();
			
			for (auto& i : texts)
			{
				fctOfFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, i, 16, "E:/Arial.ttf"));
			}

			for (int i = sizeOfFront; i < fctOfFront.size(); i++)
			{
				fctOfEmpty.push_back(std::make_unique<FactoryOfRect>(renderer));
			}
			for (auto& i : fctOfEmpty)
			{
				static int number = 0;
				i->setProperties(50, 50);
				i->setPosition(positionX, number);
				number += 50;
			}
		};
	
	helperForMultiple(600, { "Left button - set the block","Right button - delete the block","Middle button - choose a block",
							"Clear the surface - C",
							"Change color of background Red - r (hold). Shift + '+' - up, Shift + '-' - down",
							"Change color of background Blue - b (hold). Shift + '+' - up, Shift + '-' - down",
							"Change color of background Green - g (hold). Shift + '+' - up, Shift + '-' - down",
							"Change color of background Alpha - a (hold). Shift + '+' - up, Shift + '-' - down",
							"Wheel up - size of the block+","Wheel down - size of the block-",
							"Exit - Escape"});
}

void MenuForEditor::handleRender(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < fctOfEmpty.size(); i++)
	{
		fctOfFront[i]->textToRect(fctOfEmpty[i]->getRect());
		fctOfEmpty[i]->render(renderer);
		fctOfFront[i]->render(renderer);
	}
}
