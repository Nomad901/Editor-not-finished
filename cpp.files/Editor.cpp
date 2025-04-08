#include "Editor.h"

Editor::Editor(App* app, SDL_Renderer* renderer) 
	:m_forChoose(0), size(0),
	number_b(1), menuForEditor(0),
	menu(app,renderer)
{
	SDL_Color white{ 255,255,255,255 };
	m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer,white,"Click on the button for the information!",16, "E:/Arial.ttf"));
	m_factEmpty.push_back(std::make_unique<FactoryOfRect>(renderer,"E:/LabelForText.png"));
	m_factEmpty[0]->setPosition(974, 5);
	m_factEmpty[0]->setProperties(300, 100);
	m_factFront[0]->textToRect(m_factEmpty[0]->getRect());
}

void Editor::render(SDL_Renderer* renderer)
{
	if (menuForEditor == 0) {
		m_factEmpty[0]->render(renderer);
		m_factFront[0]->render(renderer);

		//std::cout << lastEl.size() << '\n';
		for (auto& it : lastEl)
		{
			if (it.first == "Grass")
			{
				m_factGrass[it.second]->render(renderer);
			}
			else if (it.first == "Leaf")
			{
				m_factLeaf[it.second]->render(renderer);
			}
			else if (it.first == "Trees")
			{
				m_factTrees[it.second]->render(renderer);
			}
		}

		if (m_forChoose == 1) {
			m_factGrass[m_factGrass.size() - 1]->render(renderer);
			m_factLeaf[m_factLeaf.size() - 1]->render(renderer);
			m_factTrees[m_factTrees.size() - 1]->render(renderer);
			for (size_t i = 0; i < numbers.size(); i++)
			{
				m_factFront[numbers[i]]->render(renderer);
			}
		}
		else {
			if (!m_factGrass.empty() && size == 1)
			{
				m_factGrass[m_factGrass.size() - 1]->render(renderer);
				if (number_b) {
					lastEl.emplace(std::make_pair<std::string, int>("Grass", static_cast<int>(m_factGrass.size() - 1)));
					number_b = 0;
				}
			}
			if (!m_factLeaf.empty() && size == 3)
			{
				m_factLeaf[m_factLeaf.size() - 1]->render(renderer);
				if (number_b) {
					lastEl.emplace(std::make_pair<std::string, int>("Leaf", static_cast<int>(m_factLeaf.size() - 1)));
					number_b = 0;
				}
			}
			if (!m_factTrees.empty() && size == 2)
			{
				m_factTrees[m_factTrees.size() - 1]->render(renderer);
				if (number_b) {
					lastEl.emplace(std::make_pair<std::string, int>("Trees", static_cast<int>(m_factTrees.size() - 1)));
					number_b = 0;
				}
			}

		}
		auto r = rgbColors.find('r');
		auto g = rgbColors.find('g');
		auto b = rgbColors.find('b');
		auto a = rgbColors.find('a');
		SDL_SetRenderDrawColor(renderer, r->second, g->second, b->second, a->second);
	}
	else {
		menu.handleRender(renderer);
	}
}


void Editor::freezeBlock(SDL_Renderer* renderer, App* app)
{

	int posX = app->mouseX();
	int posY = app->mouseY();

	if (size == 1)
	{
		m_factGrass[m_factGrass.size() - 1]->setPosition(posX, posY);
		size = 0;
	}
	else if (size == 3)
	{
		m_factLeaf[m_factLeaf.size() - 1]->setPosition(posX, posY);
		size = 0;
	}
	else if (size == 2)
	{
		m_factTrees[m_factTrees.size() - 1]->setPosition(posX, posY);
		size = 0;
	}
}

void Editor::chooseBlock(SDL_Renderer* renderer)
{
	m_factGrass.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/grass.png"));
	m_factLeaf.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/leaf.png"));
	m_factTrees.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/wood.png"));

	m_factGrass[m_factGrass.size() - 1]->setProperties(100, 100);
	m_factLeaf[m_factLeaf.size() - 1]->setProperties(100, 100);
    m_factTrees[m_factTrees.size() - 1]->setProperties(100, 100);
	
	SDL_Color white{ 255,255,255,255 };
	
	m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "1 - Grass", 15, "E:/Arial.ttf"));
	numbers.push_back(static_cast<int>(m_factFront.size() - 1));

	m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "2 - Trees", 15, "E:/Arial.ttf"));
	numbers.push_back(static_cast<int>(m_factFront.size() - 1));

	m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "3 - Leaf", 15, "E:/Arial.ttf"));
	numbers.push_back(static_cast<int>(m_factFront.size() - 1));

	m_forChoose = 1;
}

void Editor::deleteBlock(SDL_Renderer* renderer, App* app)
{
	int mouseX = app->mouseX();
	int mouseY = app->mouseY();
	
	auto deleteElMap = [&](std::multimap<std::string, int>& obj,int number) 
	{
		size_t number_ = 0;
		for (auto it = obj.begin(); it != obj.end();++it) {
			if (it->second == number) {
				obj.erase(it);
				break;
			}
			number_++;
		}
		auto it = lastEl.begin();
		for (size_t i = 0; i < lastEl.size(); ++i)
		{
			if (i >= number_) {
				it->second--;
				it++;
			}
			else { ++it; }
		}
	};
	auto deleteFromExact = [&](std::vector<std::unique_ptr<FactoryOfRect>>& obj)
		{
			auto it = obj.begin();
			for (size_t i = 0; i < obj.size(); i++)
			{
				if (obj[i]->mouseInRect(mouseX, mouseY))
				{
					it = obj.erase(it);
					deleteElMap(lastEl, static_cast<int>(i));
					break;
				}
				else it++;
			}
		};

	deleteFromExact(m_factGrass);
	deleteFromExact(m_factLeaf);
	deleteFromExact(m_factTrees);

	for (auto& i : lastEl)
	{
		std::cout << i.second << " : " << i.first << '\n';
	}
}


void Editor::forApp(int& number, SDL_Renderer* renderer, App* app)
{
	if (menuForEditor == 0) {
		static int w = 100;
		static int h = 100;

		//std::cout<<std::format("w: {}, h: {}\n", w, h);

		auto currentTexture = [&](std::vector<std::unique_ptr<FactoryOfRect>>& obj)
			{
				obj[obj.size() - 1]->setPosition(app->mouseX(), app->mouseY());
				obj[obj.size() - 1]->setProperties(w, h);
			};
		auto hideImpl = [&]() {
			if (!m_factGrass.empty()) m_factGrass.pop_back();
			if (!m_factLeaf.empty())  m_factLeaf.pop_back();
			if (!m_factTrees.empty()) m_factTrees.pop_back();
			for (size_t i = 0; i < 3; ++i)
			{
				if (!m_factFront.empty()) m_factFront.pop_back();
			}
			m_forChoose = 0;
			size = 0;
			number_b = 1;
			};
		auto plusOrMinus = [&](SDL_Event event) 
		{
				const Uint8* state = SDL_GetKeyboardState(NULL);
				bool shift = state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT];

				auto r = rgbColors.find('r');
				auto g = rgbColors.find('g');
				auto b = rgbColors.find('b');
				auto a = rgbColors.find('a');

				if ((event.key.keysym.sym == SDLK_EQUALS || event.key.keysym.sym == SDLK_PLUS) && shift) {
					if (state[SDL_SCANCODE_R]) {
						std::cout << "R++\n";
						r->second++;
					}
					else if (state[SDL_SCANCODE_G]) {
						std::cout << "G++\n";
						g->second++;
					}
					else if (state[SDL_SCANCODE_B]) {
						std::cout << "B++\n";
						b->second++;
					}
					else if (state[SDL_SCANCODE_A]) {
						std::cout << "A++\n";
						a->second++;
					}
				}

				else if ((event.key.keysym.sym == SDLK_MINUS || event.key.keysym.sym == SDLK_UNDERSCORE) && shift) {
					if (state[SDL_SCANCODE_R]) {
						std::cout << "R--\n";
						r->second--;
					}
					else if (state[SDL_SCANCODE_G]) {
						std::cout << "G--\n";
						g->second--;
					}
					else if (state[SDL_SCANCODE_B]) {
						std::cout << "B--\n";
						b->second--;
					}
					else if (state[SDL_SCANCODE_A]) {
						std::cout << "A--\n";
						a->second--;
					}
				}

		};
		
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (size == 1) currentTexture(m_factGrass);
			else if (size == 3) currentTexture(m_factLeaf);
			else if (size == 2) currentTexture(m_factTrees);

			if (m_forChoose == 1) {
				m_factGrass[m_factGrass.size() - 1]->setPosition(app->mouseX(), app->mouseY());
				m_factFront[numbers[0]]->textToRect(m_factGrass[m_factGrass.size() - 1]->getRect());
				m_factLeaf[m_factLeaf.size() - 1]->setPosition(app->mouseX(), app->mouseY() - 200);
				m_factFront[numbers[2]]->textToRect(m_factLeaf[m_factLeaf.size() - 1]->getRect());
				m_factTrees[m_factTrees.size() - 1]->setPosition(app->mouseX(), app->mouseY() - 100);
				m_factFront[numbers[1]]->textToRect(m_factTrees[m_factTrees.size() - 1]->getRect());

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
					if (size == 1) currentTexture(m_factGrass);
					else if (size == 3) currentTexture(m_factLeaf);
					else if (size == 2) currentTexture(m_factTrees);
				}
				if (event.wheel.y < 0) {
					std::cout << "Mouse wheel down\n";
					w--;h--;
					if (size == 1) currentTexture(m_factGrass);
					else if (size == 3) currentTexture(m_factLeaf);
					else if (size == 2) currentTexture(m_factTrees);
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					std::cout << "left\n";
					if (size != 0) freezeBlock(renderer, app);
					else {
						SDL_Rect rect = m_factEmpty[0]->getRect();
						if (app->mouseX() > rect.x && app->mouseX() < (rect.x + rect.w)
							&& app->mouseY() > rect.y && app->mouseY() < (rect.y + rect.h))
							menuForEditor = 1;
					}
				}
				else if (event.button.button == SDL_BUTTON_RIGHT) {
					std::cout << "right\n";
					deleteBlock(renderer, app);
				}
				else if (event.button.button == SDL_BUTTON_MIDDLE) {
					std::cout << "middle\n";
					if (m_forChoose == 0) {
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
				else if (event.key.keysym.sym == SDLK_r) {
					std::cout << "R\n";
					plusOrMinus(event);
				}
				else if (event.key.keysym.sym == SDLK_g) {
					std::cout << "G\n";
					plusOrMinus(event);
				}
				else if (event.key.keysym.sym == SDLK_b) {
					std::cout << "B\n";
					plusOrMinus(event);
				}
				else if (event.key.keysym.sym == SDLK_a) {
					std::cout << "A\n";
					plusOrMinus(event);
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
				menuForEditor = 0;
			}
		}
	}
}

void Editor::keeperBlock(int number, SDL_Renderer* renderer)
{
	if (number == 1) {
		size = 1;
		m_factGrass.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/grass.png"));
	}
	else if (number == 3) {
		size = 3;
		m_factLeaf.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/leaf.png"));
	}
	else if (number == 2) {
		size = 2;
		m_factTrees.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/wood.png"));
	}
	else {
		size = 0;
		std::cout << "Nothing is gonna happen!\n";
	}
}




//TODO: when im keeping the block(exactly 1 block) and when i wanna choose another via middle button of the mouse, then my last block is just freezing on the spot
