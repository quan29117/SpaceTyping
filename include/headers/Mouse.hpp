#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>

class Mouse {
private:
    SDL_Texture* m_texture;
    SDL_FRect m_rect;

public:
    Mouse();

    SDL_FRect getRect();

    void update();
    void render();
};