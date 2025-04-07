
export module MenuForEditor;

import <iostream>;
import <vector>;
import <memory>;
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

	void handleInstructions(App* app);
	void handleRender(SDL_Renderer* renderer);

private:
	std::vector<std::unique_ptr<FactoryOfFront>> fctOfFront;
	std::vector<std::unique_ptr<FactoryOfRect>> fctOfEmpty;
};


MenuForEditor::MenuForEditor(App* app, SDL_Renderer* renderer)
{
	SDL_Color white{ 255,255,255,255 };
	fctOfFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Left button - set the block", 16, "E:/Arial.ttf"));
	fctOfFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Right button - delete the block", 16, "E:/Arial.ttf"));
	fctOfFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Middle button - choose a block", 16, "E:/Arial.ttf"));
	fctOfFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Clear the surface - C", 16, "E:/Arial.ttf"));
	fctOfFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Wheel up - size of the block+", 16, "E:/Arial.ttf"));
	fctOfFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Exit - Escape", 16, "E:/Arial.ttf"));

	for (int i = 0; i < fctOfFront.size(); i++)
	{
		fctOfEmpty.push_back(std::make_unique<FactoryOfRect>(renderer));
	}
	for (auto& i : fctOfEmpty)
	{
		static int number = 0;
		i->setProperties(50, 50);
		i->setPosition(app->dimensionX()*2, number);
		number += 50;
	}
}

void MenuForEditor::handleInstructions(App* app)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.key.keysym.sym == SDL_QUIT) {
			app->stopLoop();
		}
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			std::cout << "escape\n";
			
		}
	}
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
