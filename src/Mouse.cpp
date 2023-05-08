/*******************************************************************//*
 * Implementation of the Mouse class.
 *
 *********************************************************************/

#include <headers/Mouse.hpp>

#include <SDL2/SDL_mouse.h>
#include <headers/Global.hpp>
#include <headers/Application.hpp>
#include <headers/Structs.hpp>

Mouse::Mouse() {
    m_texture = Application::getResourceManager()->getTexture(mouse);

    m_dest.w = MOUSE_WIDTH;
    m_dest.h = MOUSE_HEIGHT;

    m_point.w = m_point.h = MOUSE_POINT_SIZE;
}

SDL_FRect& Mouse::getPoint() {
    return m_point;
}

void Mouse::update() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    m_dest.x = m_point.x = x;
    m_dest.y = m_point.y = y;
}

void Mouse::render() {
    TextureManager::render(m_texture, nullptr, &m_dest);
}