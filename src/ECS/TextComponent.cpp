#include <headers/ECS/TextComponent.hpp>

#include <headers/Game.hpp>
#include <headers/Structs.hpp>

TextComponent::TextComponent(const FontID& id, const std::string& text, const bool& render)
    : m_id (id), m_text (text), m_render (render)
{}

TextComponent::~TextComponent() {}

char TextComponent::getFirstChar() {
    if (m_text.size() > 0)
        return m_text[0];
    else return '\0';
}

void TextComponent::init() {
    if (entity->hasComponent<TransformComponent>()) {
        m_trans = &entity->getComponent<TransformComponent>();
        m_destRect.x = (int) m_trans->position.x;
        m_destRect.y = (int) m_trans->position.y;
    }
    else std::cout << "No TransformComponent\n";

    if (m_render) setText();
}

void TextComponent::update() {
    m_destRect.x = (int) m_trans->position.x;
    m_destRect.y = (int) m_trans->position.y;
}

void TextComponent::render() {
    if (m_render)
        SDL_RenderCopy(Game::getRenderer(), m_texture, nullptr, &m_destRect);
}

void TextComponent::setText() {
    SDL_Surface* surface = TTF_RenderText_Blended(Game::getResourceManager()->getFont(m_id), m_text.c_str(), SDL_Color {255,255,255,255});
    m_texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);
    if (m_texture == nullptr)
        std::cout << "Unable to create texture TextComponent\n";
    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_destRect.w, &m_destRect.h);
}

void TextComponent::eraseFirstChar() {
    if (m_text.size() > 0)
        m_text.erase(0, 1);
}