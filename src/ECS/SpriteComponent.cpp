#include <headers/ECS/SpriteComponent.hpp>

#include <headers/Game.hpp>
#include <headers/Structs.hpp>

SpriteComponent::SpriteComponent(const SpriteID& id, const float& des_w, const float& des_h) {
    m_texture = Game::getResourceManager()->getTexture(id);

    m_destRect.w = des_w;
    m_destRect.h = des_h;
}

SpriteComponent::~SpriteComponent() {
    // SDL_DestroyTexture(m_texture);
}

SDL_FRect SpriteComponent::getHitBox() {
    return m_destRect;
}

void SpriteComponent::init() {
    if (entity->hasComponent<TransformComponent>()) {
        m_trans = &entity->getComponent<TransformComponent>();
        m_destRect.x = m_trans->position.x;
        m_destRect.y = m_trans->position.y;
    }
        
    else std::cout << "No TransformComponent\n";
}

void SpriteComponent::update() {
    m_destRect.x = m_trans->position.x;
    m_destRect.y = m_trans->position.y;
}

void SpriteComponent::render() {
    TextureManager::render(m_texture, &m_destRect);
}