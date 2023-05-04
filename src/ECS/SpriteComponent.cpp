#include <headers/ECS/SpriteComponent.hpp>

#include <headers/Application.hpp>
#include <headers/Structs.hpp>

SpriteComponent::SpriteComponent(const TextureID& id, const float& dest_w, const float& dest_h) {
    m_texture = Application::getResourceManager()->getTexture(id);

    m_destRect.w = dest_w;
    m_destRect.h = dest_h;
}

SpriteComponent::~SpriteComponent() {
    m_texture = nullptr;
    m_trans = nullptr;
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
    if (m_texture != nullptr)
        TextureManager::render(m_texture, &m_destRect);
}