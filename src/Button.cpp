/*******************************************************************//*
 * Implementation of the Button class.
 *
 *********************************************************************/

#include <headers/Button.hpp>

#include <headers/Global.hpp>
#include <headers/Application.hpp>
#include <headers/Structs.hpp>

Button::Button(const SDL_Rect& src_idle, const SDL_Rect& src_hover , const SDL_FRect& dest) {
    m_texture = Application::getResourceManager()->getTexture(button);

    m_src_idle = src_idle;
    m_src_hover = src_hover;
    m_dest = dest;

    m_status = idle;
}

Button::~Button() {
    m_texture = nullptr;
}

bool Button::isHovered() {
    return (m_status == hover);
}

void Button::update(Mouse& mouse) {
    if (SDL_HasIntersectionF(&m_dest, &mouse.getPoint())) {
        if (m_status != hover)
            AudioManager::playSound(button_hover);
        m_status = hover;
    }
    else m_status = idle;
}

void Button::render() {
    if (m_status == idle)
        TextureManager::render(m_texture, &m_src_idle, &m_dest);
    else 
        TextureManager::render(m_texture, &m_src_hover, &m_dest);
}