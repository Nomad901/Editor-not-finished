#include "Menu.h"

Menu::Menu() 
{
	pImpl = std::make_unique<impl>();
	pImplForRenderer = pImpl.get();
}

Menu& Menu::getInstance()
{
	static Menu instance;
	return instance;
}

void Menu::background(SDL_Window* window, SDL_Renderer* renderer, std::string backgroundPath){
		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		FactoryOfRect f(renderer, backgroundPath.c_str());
		f.setProperties(w, h);
		f.render(renderer);
};


int Menu::buttons(SDL_Renderer* renderer)
{
	if (TTF_Init() == -1)
		std::cout << "Couldnt initiazlize TTF! " << TTF_GetError() << '\n';
	SDL_Color white = { 255, 255, 255, 255 };
	pImpl->m_textVct.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Play", 24, "E:/Arial.ttf"));
	pImpl->m_textVct.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Editor", 24, "E:/Arial.ttf"));
	pImpl->m_textVct.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Settings", 24, "E:/Arial.ttf"));
	pImpl->m_textVct.push_back(std::make_unique<FactoryOfFront>(renderer, white, "Exit", 24, "E:/Arial.ttf"));

	const int x = 500;
	int y = 100;
	for (int i = 0; i < 4; i++)
	{
		pImpl->m_smrtVct.push_back(std::make_unique<FactoryOfRect>(renderer, "E:/grass.png"));
	}
	for (size_t i = 0; i < pImpl->m_smrtVct.size(); i++)
	{
		pImpl->m_smrtVct[i]->setProperties(300, 100);
		pImpl->m_smrtVct[i]->setPosition(x, y);
		y += 100;
	}

	SDL_Rect rect1 = pImpl->m_smrtVct[0]->getRect();
	SDL_Rect rect2 = pImpl->m_smrtVct[1]->getRect();
	SDL_Rect rect3 = pImpl->m_smrtVct[2]->getRect();
	SDL_Rect rect4 = pImpl->m_smrtVct[3]->getRect();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		int mouseX, mouseY;
		Uint32 buttons;
		buttons = SDL_GetMouseState(&mouseX, &mouseY);
		
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (mouseX > rect1.x && mouseX < (rect1.x + rect1.w) &&
				mouseY > rect1.y && mouseY < (rect1.y + rect1.h)) 
				return 1;
			
			if (mouseX > rect2.x && mouseX < (rect2.x + rect2.w) &&
				mouseY > rect2.y && mouseY < (rect2.y + rect2.h)) 
				return 2;
			
			if (mouseX > rect3.x && mouseX < (rect3.x + rect3.w) &&
				mouseY > rect3.y && mouseY < (rect3.y + rect3.h)) 
				return 3;
			
			if (mouseX > rect4.x && mouseX < (rect4.x + rect4.w) &&
				mouseY > rect4.y && mouseY < (rect4.y + rect4.h)) 
				return 4;
		}
	}
	return 0;	
}
