export module Renderer;

import <iostream>;
import "SDL.h";
import "Editor.h";
import "Menu.h";

Editor::impl* Editor::ptrToImplForRenderer = nullptr;
MenuForEditor* Editor::menuForRenderer = nullptr;
Menu::impl* Menu::pImplForRenderer = nullptr;

export class Renderer{
public:
	Renderer();
	~Renderer();

	struct RenderForEditor : private Editor
	{
	public:
		RenderForEditor() = default;
		~RenderForEditor() {
			delete ptrToImplForRenderer;
			delete menuForRenderer;
		}
		
		static void render(App* app, SDL_Renderer* renderer)
		{		
			if (ptrToImplForRenderer->menuForEditor == 0) {
				renderBackground(renderer);

				ptrToImplForRenderer->m_factEmpty[0]->render(renderer);
				ptrToImplForRenderer->m_factFront[0]->render(renderer);

				//std::cout << lastEl.size() << '\n';
				for (auto& it : ptrToImplForRenderer->lastEl)
				{
					if (it.first == "A Grass")
					{
						ptrToImplForRenderer->m_factGrass[it.second]->render(renderer);
					}
					else if (it.first == "C Leaf")
					{
						ptrToImplForRenderer->m_factLeaf[it.second]->render(renderer);
					}
					else if (it.first == "B Trees")
					{
						ptrToImplForRenderer->m_factTrees[it.second]->render(renderer);
					}
				}

				if (ptrToImplForRenderer->m_forChoose == 1) {
					ptrToImplForRenderer->m_factGrass[ptrToImplForRenderer->m_factGrass.size() - 1]->render(renderer);
					ptrToImplForRenderer->m_factTrees[ptrToImplForRenderer->m_factTrees.size() - 1]->render(renderer);
					ptrToImplForRenderer->m_factLeaf[ptrToImplForRenderer->m_factLeaf.size() - 1]->render(renderer);
					for (size_t i = 0; i < ptrToImplForRenderer->numbers.size(); i++)
					{
						ptrToImplForRenderer->m_factFront[ptrToImplForRenderer->numbers[i]]->render(renderer);
					}
				}
				else {
					if (!ptrToImplForRenderer->m_factTrees.empty() && ptrToImplForRenderer->size == 2)
					{
						ptrToImplForRenderer->m_factTrees[ptrToImplForRenderer->m_factTrees.size() - 1]->render(renderer);
						if (ptrToImplForRenderer->number_b) {
							ptrToImplForRenderer->lastEl.emplace(std::make_pair<std::string, int>("B Trees", static_cast<int>(ptrToImplForRenderer->m_factTrees.size() - 1)));
							ptrToImplForRenderer->number_b = 0;
						}
					}
					if (!ptrToImplForRenderer->m_factGrass.empty() && ptrToImplForRenderer->size == 1)
					{
						ptrToImplForRenderer->m_factGrass[ptrToImplForRenderer->m_factGrass.size() - 1]->render(renderer);
						if (ptrToImplForRenderer->number_b) {
							ptrToImplForRenderer->lastEl.emplace(std::make_pair<std::string, int>("A Grass", static_cast<int>(ptrToImplForRenderer->m_factGrass.size() - 1)));
							ptrToImplForRenderer->number_b = 0;
						}
					}
					if (!ptrToImplForRenderer->m_factLeaf.empty() && ptrToImplForRenderer->size == 3)
					{
						ptrToImplForRenderer->m_factLeaf[ptrToImplForRenderer->m_factLeaf.size() - 1]->render(renderer);
						if (ptrToImplForRenderer->number_b) {
							ptrToImplForRenderer->lastEl.emplace(std::make_pair<std::string, int>("C Leaf", static_cast<int>(ptrToImplForRenderer->m_factLeaf.size() - 1)));
							ptrToImplForRenderer->number_b = 0;
						}
					}
				}
				SDL_RenderPresent(renderer);
			}
			else {
				menuForRenderer->handleRender(renderer);
			}
		}
		static void renderBackground(SDL_Renderer* renderer) {
			auto r = ptrToImplForRenderer->rgbColors.find('r');
			auto g = ptrToImplForRenderer->rgbColors.find('g');
			auto b = ptrToImplForRenderer->rgbColors.find('b');
			auto a = ptrToImplForRenderer->rgbColors.find('a');
			SDL_SetRenderDrawColor(renderer, r->second, g->second, b->second, a->second);
			SDL_Rect background = { 0,0, 1280,720 };
			SDL_RenderFillRect(renderer, &background);
		}

	};
	struct RenderMenu : private Menu
	{
	public:
		RenderMenu() = default;
		~RenderMenu() {
			delete pImplForRenderer;
		}

		static void render(SDL_Renderer* renderer) {
			for (size_t i = 0; i < 4; i++)
			{
				pImplForRenderer->m_textVct[i]->textToRect(pImplForRenderer->m_smrtVct[i]->getRect());
				pImplForRenderer->m_textVct[i]->render(renderer);
			}
		}
	};

private:
	SDL_Renderer* renderer;

};

Renderer::Renderer()
	:renderer(nullptr)
{}

Renderer::~Renderer() {
	if(renderer) SDL_DestroyRenderer(renderer);
}
