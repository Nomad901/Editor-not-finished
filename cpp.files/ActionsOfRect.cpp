#include "ActionsOfRect.h"


SDL_bool ActionsOfRect::isColliding(FactoryOfRect* first, FactoryOfRect* second)
{
	const SDL_Rect first1  = first->getRect();
	const SDL_Rect second1 = second->getRect();
	return SDL_HasIntersection(&first1, &second1);
}
