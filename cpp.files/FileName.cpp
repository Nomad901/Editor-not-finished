#include <iostream>
#include <vector>
#include <string>
#include <print>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "FactoryOfRect.h"
#include "App.h"
#include "ActionsOfRect.h"
#include "Menu.h"
#include "FactoryOfFront.h"
#include "SurfacesA.h"
#include "Editor.h"
#include "Music.h"
#include "outro.h"

import Renderer;

static App* app;
static Editor* editor;
static Music* music;
static outro* outro_;

void actions() {
    SDL_Event event;
    ActionsOfRect actions;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            app->stopLoop();
        if (event.button.button == SDL_BUTTON_LEFT) {
            std::cout << app->mouseX() << " , " << app->mouseY()<<'\n';
            
        }
    }
}

void outroMain() { 

    auto gameLambda     = [&]() 
    {
        std::cout << "This wont be working for a while!\n";
    };
    auto editorLambda   = [&]() 
    {
        if (!editor)
            editor = new Editor(app, app->getRenderer());
        Renderer::RenderForEditor::render(app, app->getRenderer());
        app->actionOfLoop([&]()->void { editor->HandleActions(outro_->getNumber(), app->getRenderer(), app);});
    };
    auto settingsLambda = [&]()
    {
        std::cout << "This wont be working for a while!\n";
    };
    auto exitLambda     = [&]()
    {
        app->stopLoop();
    };
    auto menuLambda     = [&]() -> int
    {
        Menu::getInstance().background(app->getWindow(), app->getRenderer(), "E:/output-onlinepngtools.png");
        int number = Menu::getInstance().buttons(app->getRenderer());
        Renderer::RenderMenu::render(app->getRenderer());
        app->actionOfLoop(actions);
        return number;
    };
    
    outro_->appendMenu(menuLambda);
    outro_->appendFunction(Type::MAIN_EDITOR, editorLambda);
    outro_->appendFunction(Type::MAIN_EXIT, exitLambda);
        
    outro_->execute(Type::MAIN_MENU);
    if (outro_->getNumber() != 0)
        outro_->executeOfNumber();
    
}

int main(int argc, char* argv[]) {
    
    app = new App(SDL_INIT_VIDEO | SDL_INIT_AUDIO, "Minecraft 2d", 100, 100, 1280, 720);

    music = new Music("E:/01. The Journey Begins.mp3");
    music->setVolume(5);
    music->playMusic(-1);
    
    outro_ = new outro();

    app->actionOfLoop(actions);
    app->outroOfLoop(outroMain);
    app->runLoop();
 
    delete outro_;
    delete app;
    delete editor;
    delete music;
    return 0;
}

