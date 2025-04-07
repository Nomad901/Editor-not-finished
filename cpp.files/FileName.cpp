#include <iostream>
#include <vector>
#include <string>
#include <print>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "FactoryOfRect.h"
#include "App.h"
#include "ActionsOfRect.h"
#include "Menu.h"
#include "FactoryOfFront.h"
#include "SurfacesA.h"
#include "Editor.h"

static App* app;
//
//static FactoryOfRect* rect1;
//static FactoryOfRect* rect2;

static Editor* editor;

static int number = 0;

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
    //rect1->setPosition(app->mouseX(), app->mouseY());
    //rect1->setProperties(100, 100);
    //rect2->setPosition(100, 100);
    //rect2->setProperties(100, 100);   
    if (number == 4)
    {
        app->stopLoop();
    }
    else if (number == 3) {
        std::cout << "This will be working through a while! 3 \n";
    }
    else if (number == 2) {
        if (!editor) 
            editor = new Editor(app->getRenderer());
        editor->render(app->getRenderer());
        app->actionOfLoop([&]()->void { editor->forApp(number,app->getRenderer(),app);});

    }
    else if(number == 1){
        std::cout << "This will be working through a while! 3 \n";
    }
    else
    {
       Menu::getInstance().background(app->getWindow(), app->getRenderer());
       number = Menu::getInstance().buttons(app->getRenderer());
       app->actionOfLoop(actions);
    }

    //rect1->render(app->getRenderer());
    //rect2->render(app->getRenderer());
}

int main(int argc, char* argv[]) {
    
    app = new App("Minecraft 2d", 100, 100, 1280, 720);
    
    //rect1 = new FactoryOfRect(app->getRenderer(), "E:/grass.png");
    //rect2 = new FactoryOfRect(app->getRenderer(), "E:/grass.png");

    app->actionOfLoop(actions);
    app->outroOfLoop(outro);

    app->runLoop();
 
    delete app;
    //delete rect1;
    //delete rect2;
    delete editor;
    return 0;
}

