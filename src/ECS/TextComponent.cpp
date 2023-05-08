/*******************************************************************//*
 * Implementation of the TextComponent class.
 *
 *********************************************************************/

#include <headers/ECS/TextComponent.hpp>

#include <headers/Application.hpp>
#include <headers/Global.hpp>

TextComponent::TextComponent(const FontID& id, const std::string& text, const bool& center, const bool& render, const SDL_Color& color)
    : m_render (render), m_center (center), m_text_display (text), m_text_ref (text), m_font_id (id), m_color (color)
{}

TextComponent::~TextComponent() {}

void TextComponent::setText() {
    SDL_Surface* surface = TTF_RenderText_Blended(Application::getResourceManager()->getFont(m_font_id), m_text_display.c_str(), m_color);
    m_texture = SDL_CreateTextureFromSurface(Application::getRenderer(), surface);
    if (m_texture == nullptr && m_text_display.size() > 0)
        std::cout << "Unable to create texture TextComponent\n";
        
    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_destRect.w, &m_destRect.h);
}

void TextComponent::setPos() {
    SDL_FRect rect = sprite->getHitBox();

    if (m_center) {
        m_destRect.x = (int) (rect.x + rect.w / 2 - m_destRect.w / 2);
        m_destRect.y = (int) (rect.y + rect.h / 2 - m_destRect.h / 2);
    } else {
    //Special allignment for Enemy
        m_destRect.x = (int) (rect.x + ENEMY_CENTER_X - m_destRect.w / 2);
        m_destRect.y = (int) (rect.y + ENEMY_CENTER_Y - m_destRect.h / 2);
    }
}


char TextComponent::getFirstChar() {
    if (m_text_ref.size() > 0)
		return m_text_ref[0];
    return '\0';
}

char TextComponent::getCharNeedTyped() {
    if (m_text_display.size() > 0)
        return m_text_display[0];
    return '\0';
}

int TextComponent::remainingSize() {
    return m_text_display.size();
}

bool TextComponent::isFinished() {
    return (!entity->isAlive() || m_text_display.size() == 0);
}

void TextComponent::init() {
    if (entity->hasComponent<SpriteComponent>()) {
        sprite = &entity->getComponent<SpriteComponent>();
        setText();
        setPos();
    }
    else std::cout << "No SpriteComponent\n";
}

void TextComponent::update() {
    setPos();
    if (m_text_ref.size() == 0) {
        entity->destroy();
    }
}

void TextComponent::render() {
    if (m_render)
        SDL_RenderCopy(Application::getRenderer(), m_texture, nullptr, &m_destRect);
}

void TextComponent::Typed() {
    /**
		Erase the first char of text display when being * typed *
	 */

    if (m_text_display.size() > 0) {
        m_text_display.erase(0, 1);
        setText();
    }
}

void TextComponent::Shot() {
    /**
		Erase the first char of text_ref when being * hit *
	 */

    if (m_text_ref.size() > 0)
        m_text_ref.erase(0,1);
}

void TextComponent::setColor(const SDL_Color& color) {
    m_color = color;
    setText();
}