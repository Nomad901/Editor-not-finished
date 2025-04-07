#include "App.h"

App::App(const std::string title, const int x, const int y, const int w, const int h)
{
	seter();

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		std::println("Couldn't initialize SDL! Error: {}", SDL_GetError());
	else
		std::println("Its all good man!");

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0) 
		std::println("Couldn't initialize IMG PNG! Error: {}", IMG_GetError());

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) == 0)
		std::println("Couldn't initialize IMG JPG! Error: {}", IMG_GetError());

	m_window = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (!m_window)
		std::println("Couldnt initialize the window(variable)!");

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer)
		std::println("Couldnt initialize the renderer!");
}

App::~App()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void App::actionOfLoop(std::function<void(void)> func)
{
	m_func1 = func;
}

void App::outroOfLoop(std::function<void(void)> func)
{
	m_func2 = func;
}

void App::runLoop()
{
    while (m_isRunning) {
		Uint32 buttons;
		buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);

		m_func1();

		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(m_renderer);

		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		m_func2();

		SDL_RenderPresent(m_renderer);
		SDL_Delay(16);
    }
}


void App::stopLoop()
{
	m_isRunning = false;
}

void App::clearWindow()
{
	SDL_RenderClear(m_renderer);
}

void App::seter()
{
	m_isRunning = 1;
	m_mouseX = 0;
	m_mouseY = 0;
	m_window = nullptr;
	m_renderer = nullptr;
	m_func1 = nullptr;
	m_func2 = nullptr;
}
