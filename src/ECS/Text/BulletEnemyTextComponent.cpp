/*******************************************************************//*
 * Implementation of the BulletEnemyTextComponent class.
 *
 *********************************************************************/
//SDL_Color {255, 255, 255, 255}
#include <headers/ECS/Text/BulletEnemyTextComponent.hpp>

#include <headers/Application.hpp>
#include <headers/Global.hpp>

BulletEnemyTextComponent::BulletEnemyTextComponent(const std::string& text, const FontID& id) {
    m_text_ref = m_text_display = text;
    m_font_id = id;
    m_color = SDL_Color {255, 0, 0, 255};
}

BulletEnemyTextComponent::~BulletEnemyTextComponent() {}

void BulletEnemyTextComponent::setPos() {
    SDL_FRect rect = sprite->getRect();

    m_destRect.x = (int) (rect.x + rect.w / 2 - m_destRect.w / 2);
    m_destRect.y = (int) (rect.y + rect.h / 2 - m_destRect.h / 2);
}

void BulletEnemyTextComponent::init() {
    if (entity->hasComponent<SpriteComponent>()) {
        sprite = &entity->getComponent<SpriteComponent>();
        setText();
        setPos();
    }
    else std::cout << "No SpriteComponent in BulletEnemy\n";
}

void BulletEnemyTextComponent::update() {
    setPos();
    if (m_text_ref.size() == 0) {
        entity->destroy();
    }
}

void BulletEnemyTextComponent::render() {
    SDL_RenderCopy(Application::getRenderer(), m_texture, nullptr, &m_destRect);
}