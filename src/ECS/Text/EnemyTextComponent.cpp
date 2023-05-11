// /*******************************************************************//*
//  * Implementation of the EnemyTextComponent class.
//  *
//  *********************************************************************/

#include <headers/ECS/Text/EnemyTextComponent.hpp>

#include <headers/Application.hpp>
#include <headers/Global.hpp>

EnemyTextComponent::EnemyTextComponent() {}

EnemyTextComponent::EnemyTextComponent(const std::string& text, const FontID& id) {
    m_text_ref = m_text_display = text;
    m_font_id = id;
    m_color = SDL_Color {255, 255, 255, 255};
}

EnemyTextComponent::~EnemyTextComponent() {}

void EnemyTextComponent::setText() {
    SDL_Surface* surface = TTF_RenderText_Blended(Application::getResourceManager()->getFont(m_font_id), m_text_display.c_str(), m_color);
    m_texture = SDL_CreateTextureFromSurface(Application::getRenderer(), surface);
    if (m_texture == nullptr && m_text_display.size() > 0)
        std::cout << "Unable to create texture TextComponent\n";
        
    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_destRect.w, &m_destRect.h);
}

void EnemyTextComponent::setPos() {
    SDL_FRect rect = sprite->getRect();

    m_destRect.x = (int) (rect.x + ENEMY_CENTER_X - m_destRect.w / 2);
    m_destRect.y = (int) (rect.y + ENEMY_CENTER_Y - m_destRect.h / 2);
}

char EnemyTextComponent::getCharNeedTyped() {
    if (m_text_display.size() > 0)
        return m_text_display[0];
    return '\0';
}

int EnemyTextComponent::remainingSize() {
    return m_text_display.size();
}

bool EnemyTextComponent::isFinished() {
    return (!entity->isAlive() || m_text_display.size() == 0);
}

void EnemyTextComponent::init() {
    if (entity->hasComponent<SpriteComponent>()) {
        sprite = &entity->getComponent<SpriteComponent>();
        setText();
        setPos();
    }
    else std::cout << "No SpriteComponent in Enemy\n";
}

void EnemyTextComponent::update() {
    setPos();
    if (m_text_ref.size() == 0) {
        entity->destroy();
    }
}

void EnemyTextComponent::render() {
    SDL_RenderCopy(Application::getRenderer(), m_texture, nullptr, &m_destRect);
}

void EnemyTextComponent::Typed() {
    /**
		Erase the first char of text display when being * typed *
	 */

    if (m_text_display.size() > 0) {
        m_text_display.erase(0, 1);
        setText();
    }
}

void EnemyTextComponent::setColor(const SDL_Color& color) {
    m_color = color;
    setText();
}