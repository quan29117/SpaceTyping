#include <headers/ECS/ColliderComponent.hpp>

ColliderComponent::ColliderComponent(const std::string& tag) {
    m_tag = tag;
}

SDL_FRect ColliderComponent::getCollider() {
    return m_collider;
}

void ColliderComponent::init() {
    if (entity->hasComponent<TransformComponent>())
        m_trans = &entity->getComponent<TransformComponent>();
    else std::cout << "No TransformComponent\n";
}

void ColliderComponent::update() {
    m_collider.x = m_trans->position.x;
    m_collider.y = m_trans->position.y;
}