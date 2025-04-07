#pragma once
#include <string>
#include <SDL/SDL.h> 
#include <SDL/SDL_image.h>
#include "ResourceManager.h"

class AnimatedSprite {
public:
    // Constructor
    AnimatedSprite(SDL_Renderer*& renderer, std::string filepath);
    // Destructor
    ~AnimatedSprite();
    // 
    void Draw(int x, int y, int w, int h);

    // Select and play a specific frame
    void PlayFrame(int x, int y, int w, int h, int frame);

    // Update every frame
    void Update();
    // Render
    void Render(SDL_Renderer*& renderer);

private:
    SDL_Rect m_src;         // Where we're selecting from
    SDL_Rect m_dst;   // Where we are rendering
    SDL_Texture* m_texture;
};

