#include <headers/ECS/LockEnemyComponent.hpp>
#include <headers/ECS/TextComponent.hpp>

LockEnemyComponent::LockEnemyComponent() {
    m_lock_enemy = nullptr;
}

LockEnemyComponent::~LockEnemyComponent() {

}

bool LockEnemyComponent::isFree() {
    return (m_lock_enemy == nullptr);
}

char LockEnemyComponent::getCharNeedTyped() {
    return (*m_text)[0];
}

void LockEnemyComponent::init() {

}

void LockEnemyComponent::update() {

}

void LockEnemyComponent::render() {

}

void LockEnemyComponent::changeColorText() {
    if (m_lock_enemy != nullptr && m_lock_enemy->hasComponent<TextComponent>()) {
        m_lock_enemy->getComponent<TextComponent>().changeTextColor(SDL_Color {255, 0, 0, 255});
    }
}

void LockEnemyComponent::lock(Entity* enemy) {
    m_lock_enemy = enemy;
    // &m_text = enemy->getComponent<TextComponent>().getTextDisplay();
}

void LockEnemyComponent::freeLock() {
    m_lock_enemy = nullptr;
    m_text = nullptr;
}