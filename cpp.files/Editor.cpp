#include "Editor.h"

Editor::Editor(App* app, SDL_Renderer* renderer) 
{
	menu = std::make_unique<MenuForEditor>(app,renderer);
	SDL_Color white{ 255,255,255,255 };
	ptrToImpl->m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer,white,"Click on the button for the information!",16, "E:/Arial.ttf"));
	ptrToImpl->m_factEmpty.push_back(std::make_unique<FactoryOfRect>(renderer,"E:/LabelForText.png"));
	ptrToImpl->m_factEmpty[0]->setPosition(974, 5);
	ptrToImpl->m_factEmpty[0]->setProperties(300, 100);
	ptrToImpl->m_factFront[0]->textToRect(ptrToImpl->m_factEmpty[0]->getRect());
}


void Editor::freezeBlock(SDL_Renderer* renderer, App* app)
{
	int posX = app->mouseX();
	int posY = app->mouseY();

	if (ptrToImpl->size == 1)
	{
		ptrToImpl->m_factGrass[ptrToImpl->m_factGrass.size() - 1]->setPosition(posX, posY);
		ptrToImpl->size = 0;
	}
	else if (ptrToImpl->size == 2)
	{
		ptrToImpl->m_factTrees[ptrToImpl->m_factTrees.size() - 1]->setPosition(posX, posY);
		ptrToImpl->size = 0;
	}
	else if (ptrToImpl->size == 3)
	{
		ptrToImpl->m_factLeaf[ptrToImpl->m_factLeaf.size() - 1]->setPosition(posX, posY);
		ptrToImpl->size = 0;
	}
}

void Editor::chooseBlock(SDL_Renderer* renderer)
{
	ptrToImpl->m_factGrass.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/grass.png"));
	ptrToImpl->m_factTrees.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/wood.png"));
	ptrToImpl->m_factLeaf.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/leaf.png"));

	ptrToImpl->m_factGrass[ptrToImpl->m_factGrass.size() - 1]->setProperties(100, 100);
	ptrToImpl->m_factTrees[ptrToImpl->m_factTrees.size() - 1]->setProperties(100, 100);
	ptrToImpl->m_factLeaf[ptrToImpl->m_factLeaf.size() - 1]->setProperties(100, 100);
	
	SDL_Color white{ 255,255,255,255 };
	
	ptrToImpl->m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "1 - Grass", 15, "E:/Arial.ttf"));
	ptrToImpl->numbers.push_back(static_cast<int>(ptrToImpl->m_factFront.size() - 1));

	ptrToImpl->m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "2 - Trees", 15, "E:/Arial.ttf"));
	ptrToImpl->numbers.push_back(static_cast<int>(ptrToImpl->m_factFront.size() - 1));

	ptrToImpl->m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "3 - Leaf", 15, "E:/Arial.ttf"));
	ptrToImpl->numbers.push_back(static_cast<int>(ptrToImpl->m_factFront.size() - 1));

	ptrToImpl->m_forChoose = 1;
}

void Editor::deleteBlock(SDL_Renderer* renderer, App* app)
{
	int mouseX = app->mouseX();
	int mouseY = app->mouseY();
	
	auto deleteElMap = [&](std::multimap<std::string, int>& obj,int number, std::string type) 
	{
			for (auto it = obj.begin(); it != obj.end(); ++it) {
				if (it->first == type && it->second == number) {
					it = obj.erase(it);
					break;
				}
			}
			for (auto& [key,value] : obj)
			{
				if (key == type && value > number) value--;
			}
	};
	auto deleteFromExact = [&](std::vector<std::unique_ptr<FactoryOfRect>>& obj,std::string type)
		{
			auto it = obj.begin();
			for (size_t i = 0; i < obj.size(); i++)
			{
				if (obj[i]->mouseInRect(mouseX, mouseY))
				{
					it = obj.erase(it);
					deleteElMap(ptrToImpl->lastEl, static_cast<int>(i),type);
					break;
				}
				else it++;
			}
		};

	deleteFromExact(ptrToImpl->m_factGrass,"A Grass");
	deleteFromExact(ptrToImpl->m_factLeaf,"C Leaf");
	deleteFromExact(ptrToImpl->m_factTrees,"B Trees");

	for (auto& i : ptrToImpl->lastEl)
	{
		std::cout << i.second << " : " << i.first << '\n';
	}
}

//std::tuple<bool,
//	std::vector<std::unique_ptr<FactoryOfRect>>::iterator,
//	int> grass = deleteFromExact(m_factGrass);
//std::tuple<bool,
//	std::vector<std::unique_ptr<FactoryOfRect>>::iterator,
//	int> leaf = deleteFromExact(m_factLeaf);
//std::tuple<bool,
//	std::vector<std::unique_ptr<FactoryOfRect>>::iterator,
//	int> trees = deleteFromExact(m_factTrees);
//
//if (std::get<bool>(grass)) {
//	m_factGrass.erase(std::get<std::vector<std::unique_ptr<FactoryOfRect>>::iterator>(grass));
//	deleteElMap(lastEl, std::get<int>(grass));
//}
//else if (std::get<bool>(leaf)) {
//	m_factLeaf.erase(std::get<std::vector<std::unique_ptr<FactoryOfRect>>::iterator>(leaf));
//	deleteElMap(lastEl, std::get<int>(leaf));
//}
//else if (std::get<bool>(trees)) {
//	m_factTrees.erase(std::get<std::vector<std::unique_ptr<FactoryOfRect>>::iterator>(trees));
//	deleteElMap(lastEl, std::get<int>(trees));
//}

void Editor::HandleActions(int& number, SDL_Renderer* renderer, App* app)
{
	if (ptrToImpl->menuForEditor == 0) {
		static int w = 100;
		static int h = 100;

		//std::cout<<std::format("w: {}, h: {}\n", w, h);

		auto currentTexture = [&](std::vector<std::unique_ptr<FactoryOfRect>>& obj)
			{
				obj[obj.size() - 1]->setPosition(app->mouseX(), app->mouseY());
				obj[obj.size() - 1]->setProperties(w, h);
			};
		auto hideImpl = [&]() {
			if (!ptrToImpl->m_factGrass.empty()) ptrToImpl->m_factGrass.pop_back();
			if (!ptrToImpl->m_factLeaf.empty())  ptrToImpl->m_factLeaf.pop_back();
			if (!ptrToImpl->m_factTrees.empty()) ptrToImpl->m_factTrees.pop_back();
			for (size_t i = 0; i < 3; ++i)
			{
				if (!ptrToImpl->m_factFront.empty()) ptrToImpl->m_factFront.pop_back();
			}
			ptrToImpl->m_forChoose = 0;
			ptrToImpl->size = 0;
			ptrToImpl->number_b = 1;
			};
		auto plusOrMinus = [&](SDL_Event event) 
		{
				auto r = ptrToImpl->rgbColors.find('r');
				auto g = ptrToImpl->rgbColors.find('g');
				auto b = ptrToImpl->rgbColors.find('b');
				auto a = ptrToImpl->rgbColors.find('a');
		
				const Uint8* state = SDL_GetKeyboardState(NULL);
				bool shift = state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT];
				bool plus = state[SDL_SCANCODE_EQUALS] || state[SDLK_PLUS];
				bool minus = state[SDLK_UNDERSCORE] || state[SDL_SCANCODE_MINUS];
				
				if (plus) {
					if (shift && state[SDL_SCANCODE_R]) {
						std::cout << "r++ \n";
						r->second++;
					}
					else if (shift && state[SDL_SCANCODE_G]) {
						std::cout << "g++ \n";
						g->second++;
					}
					else if (shift && state[SDL_SCANCODE_B]) {
						std::cout << "b++ \n";
						b->second++;
					}
					else if (shift && state[SDL_SCANCODE_A]) {
						std::cout << "a++ \n";
						a->second++;
					}
				}
				else if (minus) {
					if (shift && state[SDL_SCANCODE_R]) {
						std::cout << "r-- \n";
						r->second--;
					}
					else if (shift && state[SDL_SCANCODE_G]) {
						std::cout << "g-- \n";
						g->second--;
					}
					else if (shift && state[SDL_SCANCODE_B]) {
						std::cout << "b-- \n";
						b->second--;
					}
					else if (shift && state[SDL_SCANCODE_A]) {
						std::cout << "a-- \n";
						a->second--;
					}
				}
		};
		
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			plusOrMinus(event);

			if (ptrToImpl->size == 1) currentTexture(ptrToImpl->m_factGrass);
			else if (ptrToImpl->size == 3) currentTexture(ptrToImpl->m_factLeaf);
			else if (ptrToImpl->size == 2) currentTexture(ptrToImpl->m_factTrees);

			if (ptrToImpl->m_forChoose == 1) {
				ptrToImpl->m_factGrass[ptrToImpl->m_factGrass.size() - 1]->setPosition(app->mouseX(), app->mouseY());
				ptrToImpl->m_factFront[ptrToImpl->numbers[0]]->textToRect(ptrToImpl->m_factGrass[ptrToImpl->m_factGrass.size() - 1]->getRect());
				ptrToImpl->m_factLeaf[ptrToImpl->m_factLeaf.size() - 1]->setPosition(app->mouseX(), app->mouseY() - 200);
				ptrToImpl->m_factFront[ptrToImpl->numbers[2]]->textToRect(ptrToImpl->m_factLeaf[ptrToImpl->m_factLeaf.size() - 1]->getRect());
				ptrToImpl->m_factTrees[ptrToImpl->m_factTrees.size() - 1]->setPosition(app->mouseX(), app->mouseY() - 100);
				ptrToImpl->m_factFront[ptrToImpl->numbers[1]]->textToRect(ptrToImpl->m_factTrees[ptrToImpl->m_factTrees.size() - 1]->getRect());

				if (event.type == SDL_KEYDOWN) {
					if (event.key.keysym.sym == SDLK_1)
					{
						hideImpl();
						keeperBlock(1, renderer);
					}
					if (event.key.keysym.sym == SDLK_2)
					{
						hideImpl();
						keeperBlock(2, renderer);
					}
					if (event.key.keysym.sym == SDLK_3)
					{
						hideImpl();
						keeperBlock(3, renderer);
					}
				}
			}

			if (event.type == SDL_QUIT) {
				app->stopLoop();
			}
			else if (event.type == SDL_MOUSEWHEEL) {
				if (event.wheel.y > 0) {
					std::cout << "Mouse wheel up\n";
					w++; h++;
					if (ptrToImpl->size == 1) currentTexture(ptrToImpl->m_factGrass);
					else if (ptrToImpl->size == 3) currentTexture(ptrToImpl->m_factLeaf);
					else if (ptrToImpl->size == 2) currentTexture(ptrToImpl->m_factTrees);
				}
				if (event.wheel.y < 0) {
					std::cout << "Mouse wheel down\n";
					w--;h--;
					if (ptrToImpl->size == 1) currentTexture(ptrToImpl->m_factGrass);
					else if (ptrToImpl->size == 3) currentTexture(ptrToImpl->m_factLeaf);
					else if (ptrToImpl->size == 2) currentTexture(ptrToImpl->m_factTrees);
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					std::cout << "left\n";
					if (ptrToImpl->size != 0) freezeBlock(renderer, app);
					else {
						SDL_Rect rect = ptrToImpl->m_factEmpty[0]->getRect();
						if (app->mouseX() > rect.x && app->mouseX() < (rect.x + rect.w)
							&& app->mouseY() > rect.y && app->mouseY() < (rect.y + rect.h))
							ptrToImpl->menuForEditor = 1;
					}
				}
				else if (event.button.button == SDL_BUTTON_RIGHT) {
					std::cout << "right\n";
					deleteBlock(renderer, app);
				}
				else if (event.button.button == SDL_BUTTON_MIDDLE) {
					std::cout << "middle\n";
					if (ptrToImpl->size != 0) {
						auto detected = [&](std::string text) {
							auto it = ptrToImpl->lastEl.begin();
							for (auto iter = ptrToImpl->lastEl.begin(); iter != ptrToImpl->lastEl.end();++iter) if (iter->first == text) it = iter;
							ptrToImpl->lastEl.erase(it);
							};

						if (ptrToImpl->size == 1) {
							if (!ptrToImpl->m_factGrass.empty()) ptrToImpl->m_factGrass.pop_back();
							detected("A Grass");
						}
						else if (ptrToImpl->size == 2) {
							if (!ptrToImpl->m_factTrees.empty()) ptrToImpl->m_factTrees.pop_back();
							detected("B Trees");
						}
						else if (ptrToImpl->size == 3) {
							if (!ptrToImpl->m_factLeaf.empty()) ptrToImpl->m_factLeaf.pop_back();
							detected("C Leaf");
						}
						ptrToImpl->size = 0;
					}
					if (ptrToImpl->m_forChoose == 0) {
						chooseBlock(renderer);
					}
					else {
						hideImpl();
					}
				}
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					std::cout << "escape\n";
					number = 0;
				}
				else if (event.key.keysym.sym == SDLK_c) {
					std::cout << "clearAll\n";
					clearAll(renderer);
				}
				else if (event.key.keysym.sym == SDLK_z) {
					std::cout << "z\n";
					auto r = ptrToImpl->rgbColors.find('r'); r->second = 0;
					auto g = ptrToImpl->rgbColors.find('g'); g->second = 0;
					auto b = ptrToImpl->rgbColors.find('b'); b->second = 0;
					auto a = ptrToImpl->rgbColors.find('a'); a->second = 0;
				}
			}
		}
	}
	else {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				app->stopLoop();
			}
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				std::cout << "escape\n";
				ptrToImpl->menuForEditor = 0;
			}
		}
	}
}

void Editor::keeperBlock(int number, SDL_Renderer* renderer)
{
	if (number == 1) {
		ptrToImpl->size = 1;
		ptrToImpl->m_factGrass.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/grass.png"));
	}
	else if (number == 3) {
		ptrToImpl->size = 3;
		ptrToImpl->m_factLeaf.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/leaf.png"));
	}
	else if (number == 2) {
		ptrToImpl->size = 2;
		ptrToImpl->m_factTrees.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/wood.png"));
	}
	else {
		ptrToImpl->size = 0;
		std::cout << "Nothing is gonna happen!\n";
	}
}




//TODO: when im keeping the block(exactly 1 block) and when i wanna choose another via middle button of the mouse, then my last block is just freezing on the spot
