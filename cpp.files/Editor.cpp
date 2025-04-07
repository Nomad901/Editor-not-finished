#include "Editor.h"

Editor::Editor(SDL_Renderer* renderer) 
	:m_forChoose(0), size(0)
{
	SDL_Color white = { 255, 255, 255, 255 };
	m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Left button - set the block", 16, "E:/Arial.ttf"));
	m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Right button - delete the block", 16, "E:/Arial.ttf"));
	m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Middle button - choose a block", 16, "E:/Arial.ttf"));
	m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Clear the surface - C", 16, "E:/Arial.ttf"));
	m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Wheel up - size of the block+", 16, "E:/Arial.ttf"));
	m_factFront.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Exit - Escape", 16, "E:/Arial.ttf"));

	for (int i = 0; i < m_factFront.size(); i++)
	{
		m_factEmpty.push_back(std::make_unique<FactoryOfRect>(renderer));
	}
	for (auto& i : m_factEmpty)
	{
		static int number = 0;
		i->setProperties(50, 50);
		i->setPosition(1100, number);
		number+=50;
	}
}

void Editor::render(SDL_Renderer* renderer)
{

	for (size_t i = 0; i < m_factEmpty.size(); i++)
	{
		m_factFront[i]->textToRect(m_factEmpty[i]->getRect());
		m_factEmpty[i]->render(renderer);
		m_factFront[i]->render(renderer);
	}
	
	std::cout << lastEl.size() << '\n';
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
			if(number_b) {
				lastEl.emplace(std::make_pair<std::string, int>("Trees", static_cast<int>(m_factTrees.size() - 1)));
				number_b = 0;
			}
		}

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

	auto it = m_factGrass.begin();
	for (size_t i = 0; i < m_factGrass.size(); i++)
	{
		if (m_factGrass[i]->mouseInRect(mouseX, mouseY))
		{
			it = m_factGrass.erase(it);
			deleteElMap(lastEl, i);
			break;
		}
		else it++;
	}
	for (auto& i : lastEl)
	{
		std::cout << i.second << " : " << i.first << '\n';
	}
}


void Editor::forApp(int& number, SDL_Renderer* renderer, App* app)
{
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

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (size == 1) {
			m_factGrass[m_factGrass.size() - 1]->setPosition(app->mouseX(), app->mouseY());
			m_factGrass[m_factGrass.size() - 1]->setProperties(100, 100);
		}
		else if (size == 3) { 
			m_factLeaf[m_factLeaf.size() - 1]->setPosition(app->mouseX(), app->mouseY()); 
			m_factLeaf[m_factLeaf.size() - 1]->setProperties(100, 100);
		}
		else if(size == 2) { 
			m_factTrees[m_factTrees.size() - 1]->setPosition(app->mouseX(), app->mouseY());
			m_factTrees[m_factTrees.size() - 1]->setProperties(100, 100);
		}

		if (m_forChoose == 1) {
			m_factGrass[m_factGrass.size() - 1]->setPosition(app->mouseX(), app->mouseY());
			m_factFront[numbers[0]]->textToRect(m_factGrass[m_factGrass.size() - 1]->getRect());
			m_factLeaf [m_factLeaf.size() - 1]->setPosition(app->mouseX(), app->mouseY()-200);
			m_factFront[numbers[2]]->textToRect(m_factLeaf[m_factLeaf.size() - 1]->getRect());
			m_factTrees[m_factTrees.size() - 1]->setPosition(app->mouseX(), app->mouseY()-100);
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
		else if (event.type == SDL_MOUSEBUTTONDOWN) {  
			if (event.button.button == SDL_BUTTON_LEFT) {
				std::cout << "left\n";
				freezeBlock(renderer, app);
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