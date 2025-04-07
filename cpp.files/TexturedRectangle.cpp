#include "TexturedRectangle.h"

TextureRectangle::TextureRectangle(SDL_Renderer*& renderer, std::string filepath)
{
    SDL_Surface* retrieveSurface = ResourceManager::getInstance().getSurface(filepath);    
    texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);
    SDL_FreeSurface(surface);
}

void TextureRectangle::setRectanglesProperties(int x, int y, int w, int h)
{
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
}

SDL_bool TextureRectangle::isColliding(TextureRectangle& obj)
{
    const SDL_Rect temp = obj.GetRectangle();
    return SDL_HasIntersection(&rectangle,&temp);
}

void TextureRectangle::update()
{
}
