#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>

class Mouse {
private:
    SDL_Texture* m_texture;
    SDL_FRect m_rect, m_point;

public:
    Mouse();
    virtual ~Mouse() {};

    SDL_FRect& getPoint();
    
    void update();
    void render();
};