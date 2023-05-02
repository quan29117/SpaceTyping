#include <headers/Mouse.hpp>

#include <SDL2/SDL_mouse.h>
#include <headers/Global.hpp>
#include <headers/Application.hpp>
#include <headers/Structs.hpp>

Mouse::Mouse() {
    m_texture = Application::getResourceManager()->getTexture(mouse);

    m_rect.h = MOUSE_HEIGHT;
    m_rect.w = MOUSE_WIDTH;

    m_point.h = m_point.w = 1;
}

SDL_FRect& Mouse::getPoint() {
    return m_point;
}

void Mouse::update() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    m_rect.x = m_point.x = x;
    m_rect.y = m_point.y = y;
}

void Mouse::render() {
    TextureManager::render(m_texture, &m_rect);
}