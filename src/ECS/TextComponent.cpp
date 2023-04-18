#include <headers/ECS/TextComponent.hpp>

#include <headers/Game.hpp>
#include <headers/Structs.hpp>

TextComponent::TextComponent(const FontID& m_id, const std::string& text) {
    id = m_id;
    m_text = text;
}

TextComponent::~TextComponent() {

}

void TextComponent::init() {
    if (entity->hasComponent<TransformComponent>()) {
        m_trans = &entity->getComponent<TransformComponent>();
        m_destRect.x = (int) m_trans->position.x;
        m_destRect.y = (int) m_trans->position.y;
    }
    else std::cout << "No TransformComponent\n";

    setText();
}

void TextComponent::update() {
    m_destRect.x = (int) m_trans->position.x;
    m_destRect.y = (int) m_trans->position.y;
}

void TextComponent::render() {
    SDL_RenderCopy(Game::getRenderer(), m_texture, nullptr, &m_destRect);
}

void TextComponent::setText() {
    SDL_Surface* surface = TTF_RenderText_Blended(Game::getResourceManager()->getFont(id), m_text.c_str(), SDL_Color {255,255,255,255});
    m_texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);
    if (m_texture == nullptr)
        std::cout << "Unable to create texture TextComponent\n";
    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_destRect.w, &m_destRect.h);
}