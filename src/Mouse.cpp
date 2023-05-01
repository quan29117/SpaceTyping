#include <headers/Mouse.hpp>

#include <SDL2/SDL_mouse.h>
#include <headers/Global.hpp>
#include <headers/Game.hpp>
#include <headers/Structs.hpp>

Mouse::Mouse() {
    m_texture = Game::getResourceManager()->getTexture(mouse);
    m_rect.h = MOUSE_HEIGHT;
    m_rect.w = MOUSE_WIDTH;
}

SDL_FRect Mouse::getRect() {
    return m_rect;
}

void Mouse::update() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    m_rect.x = x;
    m_rect.y = y;
}

void Mouse::render() {
    TextureManager::render(m_texture, &m_rect);
}