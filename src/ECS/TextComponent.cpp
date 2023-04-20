#include <headers/ECS/TextComponent.hpp>

#include <headers/Game.hpp>
#include <headers/Structs.hpp>
#include <headers/Global.hpp>

//---------------------------------TextComponent-----------------------------------
TextComponent::TextComponent(const FontID& id, const std::string& text, const bool& render, const SDL_Color& color)
    : m_id (id), m_text_display (text), m_text_ref (text), m_render (render), m_color (color)
{}

TextComponent::~TextComponent() {}

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

void TextComponent::init() {
    if (entity->hasComponent<SpriteComponent>()) {
        m_sprite = &entity->getComponent<SpriteComponent>();
        setText();
        setPos();
    }
    else std::cout << "No SpriteComponent\n";
}

void TextComponent::update() {
    setPos();
}

void TextComponent::render() {
    if (m_render)
        SDL_RenderCopy(Game::getRenderer(), m_texture, nullptr, &m_destRect);
}

void TextComponent::setPos() {
    SDL_FRect rect = m_sprite->getHitBox();

    m_destRect.x = (int) (rect.x + rect.w / 2 - m_destRect.w / 2);
    m_destRect.y = (int) (rect.y + rect.h / 2 - m_destRect.h / 2);
}

void TextComponent::setText() {
    SDL_Surface* surface = TTF_RenderText_Blended(Game::getResourceManager()->getFont(m_id), m_text_display.c_str(), m_color);
    m_texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);
    if (m_texture == nullptr && m_text_display.size() > 0)
        std::cout << "Unable to create texture TextComponent\n";
    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_destRect.w, &m_destRect.h);
}

void TextComponent::eraseFirstChar() {
    /**
		Erase the first char of word display when being * typed *
	 */

    if (m_text_display.size() > 0) {
        m_text_display.erase(0, 1);
        setText();
    }
}

//-------------------------------TextEnemyComponent--------------------------------
TextEnemyComponent::TextEnemyComponent(const FontID& id, const std::string& text) {
    m_id = id;
    m_text_display = m_text_ref = text;
    m_render = true;
    m_color = SDL_Color {255, 255, 255, 255};
}

TextEnemyComponent::~TextEnemyComponent() {}

void TextEnemyComponent::setPos() {
    SDL_FRect rect = m_sprite->getHitBox();
    
    m_destRect.x = (int) (rect.x + ENEMY_CENTER_X - m_destRect.w / 2);
    m_destRect.y = (int) (rect.y + ENEMY_CENTER_Y - m_destRect.h / 2);
}

void TextEnemyComponent::getShot() {
    /**
		Erase the first char of text_ref to make condition of collision Bullet - Enemy
	 */

    if (m_text_ref.size() > 0)
        m_text_ref.erase(0,1);
}