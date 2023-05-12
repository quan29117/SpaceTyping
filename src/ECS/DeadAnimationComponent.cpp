#include <headers/ECS/DeadAnimationComponent.hpp>

DeadAnimationComponent::DeadAnimationComponent() {}

DeadAnimationComponent::~DeadAnimationComponent() {}

void DeadAnimationComponent::init() {
    if (entity->hasComponent<SpriteComponent>()) {
        sprite = &entity->getComponent<SpriteComponent>();
    }
    else std::cout << "No SpriteComponent\n";
}

void DeadAnimationComponent::update() {
    if (sprite->isEndAnimation())
        entity->destroy();
}

void DeadAnimationComponent::render() {}