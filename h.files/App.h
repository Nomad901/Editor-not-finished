#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <print>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>

class App
{
public:
	App(const std::string title, const int x, const int y, const int w, const int h);
	~App();
	
	void actionOfLoop(std::function<void(void)> func);
	void outroOfLoop(std::function<void(void)> func);
	void runLoop();
	void stopLoop();
	void clearWindow();

	SDL_Window* getWindow() { return m_window; }
	SDL_Renderer* getRenderer() { return m_renderer; }
	int mouseX() { return m_mouseX; }
	int mouseY() { return m_mouseY; }

private:
	void seter();
	bool m_isRunning;
	int m_mouseX, m_mouseY;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	std::function<void(void)> m_func1;
	std::function<void(void)> m_func2;

};

