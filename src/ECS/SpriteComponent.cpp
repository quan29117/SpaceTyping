/*******************************************************************//*
 * Implementation of the SpriteComponent class.
 *
 *********************************************************************/

#include <headers/ECS/SpriteComponent.hpp>

#include <headers/Application.hpp>
#include <headers/Structs.hpp>

SpriteComponent::SpriteComponent(const TextureID& id, const SDL_Rect& src, const Vector2D& destSize, const bool& animated) {
    m_texture = Application::getResourceManager()->getTexture(id);

    m_src = src;
    m_dest.w = destSize.x;
    m_dest.h = destSize.y;
    
    m_animated = animated;
}

SDL_FRect SpriteComponent::getHitBox() {
    return m_dest;
}

void SpriteComponent::init() {
    if (entity->hasComponent<TransformComponent>()) {
        transform = &entity->getComponent<TransformComponent>();
        m_dest.x = transform->getPosition().x;
        m_dest.y = transform->getPosition().y;
    }
    else std::cout << "No TransformComponent\n";
}

void SpriteComponent::update() {
    if (m_animated) {
        m_src.x = m_src.w * static_cast<int> ((SDL_GetTicks() / 60) % 5);
    }

    m_dest.x = transform->getPosition().x;
    m_dest.y = transform->getPosition().y;
}

void SpriteComponent::render() {
    if (m_texture != nullptr)
        TextureManager::render(m_texture, &m_src, &m_dest);
}