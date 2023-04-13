#include <headers/ECS/SpriteComponent.hpp>

SpriteComponent::SpriteComponent(const std::string& fileName, const float& des_w, const float& des_h) {
    m_texture = TextureManager::loadTexture(fileName);

    m_destRect.w = des_w;
    m_destRect.h = des_h;
}

SpriteComponent::~SpriteComponent() {
    SDL_DestroyTexture(m_texture);
}

void SpriteComponent::init() {
    if (entity->hasComponent<TransformComponent>())
        m_trans = &entity->getComponent<TransformComponent>();
    else std::cout << "No TransformComponent\n";
}

void SpriteComponent::update() {
    m_destRect.x = m_trans->position.x;
    m_destRect.y = m_trans->position.y;
}

void SpriteComponent::render() {
    TextureManager::render(m_texture, &m_destRect);
}