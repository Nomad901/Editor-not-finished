#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "FactoryOfRect.h"

class ActionsOfRect
{
public:
	ActionsOfRect(){}
	
	SDL_bool isColliding(FactoryOfRect* first, FactoryOfRect* second);
	
private:

};

