#include <headers/Button.hpp>

#include <headers/Global.hpp>
#include <headers/Application.hpp>
#include <headers/Structs.hpp>

Button::Button(const float& src_y, const float& dest_x, const float& dest_y) {
    m_texture = Application::getResourceManager()->getTexture(button);

    m_src.x = 0;
    m_src.y = src_y;

    m_src.w = m_dest.w = BUTTON_WIDTH;
    m_src.h = m_dest.h = BUTTON_HEIGHT;

    m_dest.x = dest_x;
    m_dest.y = dest_y;
}

Button::~Button() {
    m_texture = nullptr;
}

bool Button::isSelected() {
    return selected;
}

void Button::update(Mouse& mouse) {
    if (SDL_HasIntersectionF(&m_dest, &mouse.getPoint())) {
        selected = true;
        m_src.x = 400;
        //TODO : play sound
    } else {
        selected = false;
        m_src.x = 0;
    }
}

void Button::render() {
    TextureManager::render(m_texture, &m_dest, &m_src);
}