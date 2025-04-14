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

import Renderer;

static App* app;
//
//static FactoryOfRect* rect1;
//static FactoryOfRect* rect2;

static Editor* editor;

static Music* music;

static int number = 0;

enum class GameModes { THE_GAME, THE_EDITOR, THE_SETTINGS};

void helperOutro(int number) {

}

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

void outro() { 
    //TODO: maybe i can append here enum instead of conditions
    if (number == 4)
    {
        app->stopLoop();
    }
    else if (number == 3) {
        std::cout << "This will be working through a while! 3 \n";
    }
    else if (number == 2) {
        if (!editor)
            editor = new Editor(app, app->getRenderer());
        Renderer::RenderForEditor::render(app, app->getRenderer());
        app->actionOfLoop([&]()->void { editor->HandleActions(number,app->getRenderer(),app);});
    }
    else if(number == 1){
        std::cout << "This will be working through a while! 3 \n";
    }
    else
    {
       Menu::getInstance().background(app->getWindow(), app->getRenderer(), "E:/output-onlinepngtools.png");
       number = Menu::getInstance().buttons(app->getRenderer());
       Renderer::RenderMenu::render(app->getRenderer());
       app->actionOfLoop(actions);
    }
}

int main(int argc, char* argv[]) {
    
    app = new App(SDL_INIT_VIDEO | SDL_INIT_AUDIO, "Minecraft 2d", 100, 100, 1280, 720);

    music = new Music("E:/01. The Journey Begins.mp3");
    music->setVolume(5);
    music->playMusic(-1);
    
    app->actionOfLoop(actions);
    app->outroOfLoop(outro);
    app->runLoop();
 

    delete app;
    delete editor;
    delete music;
    return 0;
}

